// File: xy_plotter_controller.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the class defined in xy_plotter_controller.hpp.

#include "xy_plotter_controller.hpp"

namespace calebrjc::XYPlotter {
long xLast;
long yLast;

int readLightSensor() {
  int value = analogRead(PIN_LIGHT_SENSOR);
  if (value > 500) digitalWrite(4, HIGH);
  else digitalWrite(500, LOW);
  return value;
}

int readBumpers(char axis) {
  if (axis == 'x') {
    return analogRead(PIN_X_BUMPERS);
  } else {
    return analogRead(PIN_Y_BUMPERS);
  }
}

void XYPlotterController::initializePlotter() {
  xLast = 0;
  yLast = 0;

  ////////// SERIAL INITIALIZAITON //////////
  Serial.begin(9600);
  while (!Serial) {
    // Halt execution until the serial interface is ready
  }  // while

  ////////// PIN INITIALIZAITON //////////
  pinMode(PIN_X2_DIRECTION, OUTPUT);
  pinMode(PIN_X2_STEP, OUTPUT);
  pinMode(PIN_X1_DIRECTION, OUTPUT);
  pinMode(PIN_X1_STEP, OUTPUT);
  pinMode(PIN_Y_DIRECTION, OUTPUT);
  pinMode(PIN_Y_STEP, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_EMERGENCY_STOP, INPUT);
  pinMode(PIN_LIGHT_SENSOR, INPUT);

  pinMode(4, OUTPUT);

  digitalWrite(PIN_ENABLE, HIGH);

  ///////////SERVO INITIALIZATION//////////
  this->servo = Servo();
  this->servo.attach(PIN_SERVO);
  penDown();

  ////////// ZEROING THE PLOTTER //////////
  penUp();
  zeroPlotter();

  ////////// STEPPER INITIALIZAITON //////////
  long stepperSpeed = 250; //was 250

  this->xStepper1 = AccelStepper(AccelStepper::DRIVER, PIN_X1_STEP, PIN_X1_DIRECTION);
  this->xStepper1.setMaxSpeed(stepperSpeed);
  this->xStepper1.setMinPulseWidth(2000);

  this->xStepper2 = AccelStepper(AccelStepper::DRIVER, PIN_X2_STEP, PIN_X2_DIRECTION);
  this->xStepper2.setMaxSpeed(stepperSpeed);
  this->xStepper2.setMinPulseWidth(2000);

  this->yStepper = AccelStepper(AccelStepper::DRIVER, PIN_Y_STEP, PIN_Y_DIRECTION);
  this->yStepper.setMaxSpeed(stepperSpeed);
  this->yStepper.setMinPulseWidth(2000);

  this->steppers = MultiStepper();
  steppers.addStepper(xStepper1);
  steppers.addStepper(xStepper2);
  steppers.addStepper(yStepper);


  // Run motors until bumpers are no longer hit
  offZero();
  
  /*
  this->xStepper1.setCurrentPosition(0);
  this->xStepper2.setCurrentPosition(0);
  this->yStepper.setCurrentPosition(0);
  this->xCurrent = 0;
  this->yCurrent = 0;
  */

  ////////// FINDING AND MEASURING THE PAPER //////////

  this->findPaper();

  this->yWidth = this->findWidth('y');
  this->setTargetCoordinates(this->xCurrent, this->yWidth - 50);
  this->runToCompletion();
  this->yOrigin = this->findOrigin('y');

  // Moving to midpoint of y axis
  Serial.println("Moving to y midpoint...");
  this->setTargetCoordinates(this->xCurrent, (this->yOrigin + this->yWidth) / 2);
  this->runToCompletion();
  Serial.println("DONE");

  this->xWidth = this->findWidth('x');
  this->setTargetCoordinates(this->xWidth - 50, this->yCurrent);
  this->runToCompletion();
  this->xOrigin = this->findOrigin('x');
  
  this->home();

  Serial.print("Y Width: ");
  Serial.println(this->yWidth);
  Serial.print("Y Origin: ");
  Serial.println(this->yOrigin);
  Serial.print("X Width: ");
  Serial.println(this->xWidth);
  Serial.print("X Origin: ");
  Serial.println(this->xOrigin);

  SerialUtil::sendMessage(SerialUtil::MESSAGE_READY);
}  // XYPlotterController::initializePlotter()

void XYPlotterController::findPaper() {
  // Detect the paper on the diagonal axis
  this->setTargetCoordinates(PLOTTER_WIDTH, PLOTTER_WIDTH);
  Serial.println("Detecting paper... (dark to light transition)");
  while (readLightSensor() > LIGHT_THRESHOLD) step();
  Serial.println("DONE");

  // Step into the paper a little
  Serial.println("Stepping into paper...");
  this->setTargetCoordinates(this->xCurrent + 70, this->yCurrent + 70);
  this->runToCompletion();
  Serial.println("DONE");
}  // findPaper

long XYPlotterController::findWidth(char axis) {
  if (axis == 'x') {
    // Finding x width
    this->setTargetCoordinates(PLOTTER_WIDTH, this->yCurrent);
    Serial.println("Detecting right edge... (light to dark transition)");
    while (readLightSensor() < LIGHT_THRESHOLD) step(); //FOREGROUND
    Serial.println("DONE");
    return this->xCurrent;
  } else {
    // Finding y width
    this->setTargetCoordinates(this->xCurrent, PLOTTER_WIDTH);
    Serial.println("Detecting bottom edge... (light to dark transition)");
    while (readLightSensor() < LIGHT_THRESHOLD) step(); //BACKGROUND
    Serial.println("DONE");
    return this->yCurrent;
  }  //  if-else
}  // findYWidth

long XYPlotterController::findOrigin(char axis) {
  if (axis == 'x') {
    // Finding x origin
    this->setTargetCoordinates(0, this->yCurrent);

    Serial.println("Detecting right edge... again... (dark to light transition)");
    while (readLightSensor() < LIGHT_THRESHOLD) step(); //Foreground
    Serial.println("DONE");
    /*
    Serial.println("Detecting left edge... (light to dark transition)");
    Serial.println("DONE");
    while (readLightSensor() > LIGHT_THRESHOLD) step();//Backgorund
    */
    return this->xCurrent;
  } else {
    // Finding y origin
    this->setTargetCoordinates(this->xCurrent, 0);

    Serial.println("Detecting bottom edge... again... (dark to light transition)");
    while (readLightSensor() < LIGHT_THRESHOLD) step(); //forground
    Serial.println("DONE");
    /*
    Serial.println("Detecting top edge... (light to dark transition)");
    while (readLightSensor() > LIGHT_THRESHOLD) step(); //bacround
    Serial.println("DONE");
    */
    return this->yCurrent;
  }  //  if-else
}  // findYOrigin

long XYPlotterController::unscale(long n, char axis) {
  long oldRange = (1000 - 0);

  if (axis == 'x') {
    long newRange = (this->xWidth - this->xOrigin);
    return ((n * newRange) / oldRange) + xOrigin;
  } else {
    long newRange = (this->yWidth - this->yOrigin);
    return ((n * newRange) / oldRange) + yOrigin;
  }  // if-else
}  // unscale

String XYPlotterController::executeCommand(Command c) {
  if (c.numParameters == -1) {
    return SerialUtil::MESSAGE_ERROR;
  }

  if (strcmp(c.instruction, COMMAND_TEST) == 0) {
    return SerialUtil::MESSAGE_OK;
  }

  if (strcmp(c.instruction, COMMAND_TURN_OFF) == 0) {
    return (this->turnOff()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  }  // if

  if (strcmp(c.instruction, COMMAND_TEST_X) == 0) {
    return (this->testX()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  }  // if

  if (strcmp(c.instruction, COMMAND_TEST_Y) == 0) {
    return (this->testY()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  }  // if

  if (strcmp(c.instruction, COMMAND_PEN_UP) == 0) {
    return (this->penUp()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  }  // if

  if (strcmp(c.instruction, COMMAND_PEN_DOWN) == 0) {
    return (this->penDown()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  }  // if

  return SerialUtil::MESSAGE_ERROR;
}  // XYPlotterController::executeCommand()

void XYPlotterController::setTargetCoordinates(long x, long y) {
  this->targetCoordinates[0] = x;
  this->targetCoordinates[1] = x;
  this->targetCoordinates[2] = y;
  this->steppers.moveTo(this->targetCoordinates);
}  // setTargetCoordinates

bool XYPlotterController::isAtTarget() {
  return (this->xCurrent == this->targetCoordinates[0]) &&
         (this->yCurrent == this->targetCoordinates[2]);
}  // isAtTarget

bool XYPlotterController::step() {
  digitalWrite(PIN_ENABLE, LOW);
  if (digitalRead(PIN_EMERGENCY_STOP) == 1 ||
           readBumpers('x') < BUMPER_PRESS || 
           readBumpers('y') < BUMPER_PRESS) {
    digitalWrite(PIN_ENABLE, HIGH);
    return false;
  }  // if

  this->steppers.run();
  this->xCurrent = this->xStepper1.currentPosition();
  this->yCurrent = this->yStepper.currentPosition();

  if (abs(this->xCurrent - xLast) > 0 || abs(this->yCurrent - yLast) > 0) {
    Serial.print("(");
    Serial.print(this->xCurrent);
    Serial.print(", ");
    Serial.print(this->yCurrent);
    Serial.println(")");
  }
  xLast = this->xCurrent;
  yLast = this->yCurrent;

  digitalWrite(PIN_ENABLE, HIGH);

  return true;
}  // step

bool XYPlotterController::runToCompletion() {
  while (!this->isAtTarget()) {
    if (!this->step()) return false;
  }  // while
  return true;
}  // runToCompletion

bool XYPlotterController::turnOff() {
  // this->penUp();
  return true;
}  // turnOff

bool setAndRun(XYPlotterController *self, long x, long y) {
  self->setTargetCoordinates(x, y);
  return self->runToCompletion();
}

bool XYPlotterController::testX() {
  bool res = setAndRun(this, 500, 500);
  delay(500);
  if (res) res = setAndRun(this, 0, 0);
  return res;
}  // testX

bool XYPlotterController::testY() {
  bool res = setAndRun(this, 450, 600);
  delay(500);
  if (res) res = setAndRun(this, 0, 0);
  return res;
}  // testY

// bool XYPlotterController::testZ() {
//   //
//   //
//   return true;
// }  // testZ

bool XYPlotterController::penUp() {
   this->servo.write(SERVO_UP_POS);
   return true;
}

bool XYPlotterController::penDown() {
   this->servo.write(SERVO_DOWN_POS);
   return true;
}

// bool move(long x1, long y1, long x2, long y2) {
//   //
//   //
//   return true;
// }  // move

void XYPlotterController::zeroPlotter() {
  digitalWrite(PIN_ENABLE, LOW);
  digitalWrite(PIN_Y_DIRECTION, LOW);
  digitalWrite(PIN_X1_DIRECTION, LOW);
  digitalWrite(PIN_X2_DIRECTION, LOW);
  
  while(readBumpers('x') > BUMPER_PRESS || readBumpers('y') > BUMPER_PRESS) {
    if (readBumpers('x') > BUMPER_PRESS) {
      moveStepper(PIN_X1_STEP);
      moveStepper(PIN_X2_STEP);
    }  // if
    if (readBumpers('y') > BUMPER_PRESS) {
      moveStepper(PIN_Y_STEP);
    }  // if
  } // while
  digitalWrite(PIN_ENABLE, HIGH);
} // zeroPlotter

void XYPlotterController::offZero() {
  digitalWrite(PIN_ENABLE, LOW);
  digitalWrite(PIN_Y_DIRECTION, HIGH);
  digitalWrite(PIN_X1_DIRECTION, HIGH);
  digitalWrite(PIN_X2_DIRECTION, HIGH);

  int stepsOff = 5;

  for (int i = 0; i < stepsOff; i++) {
    moveStepper(PIN_X1_STEP);
    moveStepper(PIN_X2_STEP);
    moveStepper(PIN_Y_STEP);
  } // for i
  this->xStepper1.setCurrentPosition(stepsOff);
  this->xStepper2.setCurrentPosition(stepsOff);
  this->yStepper.setCurrentPosition(stepsOff);
  this->xCurrent = this->xStepper1.currentPosition();
  this->yCurrent = this->yStepper.currentPosition();

  digitalWrite(PIN_ENABLE, HIGH);
} // off zero

void XYPlotterController::moveStepper(const int pin) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(2000);
  digitalWrite(pin, LOW);
  delayMicroseconds(2000);
} // move stepper

bool XYPlotterController::home() {
  this->setTargetCoordinates(this->xOrigin, this->yOrigin);
  Serial.print("Rehoming...");
  this->runToCompletion();
  Serial.println("DONE");
  return true;
}  // home

// bool drawLine(long x1, long y1, long x2, long y2) {
//   //
//   //
//   return true;
// }  // drawLone
}  // namespace calebrjc::XYPlotter
