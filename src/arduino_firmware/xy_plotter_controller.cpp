// File: xy_plotter_controller.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the class defined in xy_plotter_controller.hpp.

#include "xy_plotter_controller.hpp"

namespace calebrjc::XYPlotter {
void XYPlotterController::initializePlotter() {
  Serial.begin(9600);
  while (!Serial) {} // Halt execution until the serial interface is ready
  SerialUtil::sendMessage(SerialUtil::MESSAGE_READY);

  for (int pin = PIN_X_DIRECTION; pin <= PIN_Y_STEP; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
} // XYPlotterController::initializePlotter()

String XYPlotterController::executeCommand(Command c) {
  if (c.numParameters == -1) { return SerialUtil::MESSAGE_ERROR; }

  if (strcmp(c.instruction, COMMAND_TEST) == 0) { return SerialUtil::MESSAGE_OK; }

  if (strcmp(c.instruction, COMMAND_TURN_OFF) == 0) {
    return (this->turnOff()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  } // if

  if (strcmp(c.instruction, COMMAND_TEST_X) == 0) {
    return (this->testX()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  } // if

  if (strcmp(c.instruction, COMMAND_TEST_Y) == 0) {
    return (this->testY()) ? SerialUtil::MESSAGE_OK : SerialUtil::MESSAGE_ERROR;
  } // if

  return SerialUtil::MESSAGE_ERROR;
} // XYPlotterController::executeCommand()

bool XYPlotterController::turnOff() {
  // Code goes here.
  return true;
} // XYPlotterController::turnOff

void step(int stepPin) {
  digitalWrite(stepPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(2000);
} // step

void testMotor(int axisPin, int stepPin) {
  // Positive direction
  digitalWrite(axisPin, HIGH);
  for (int i = 0; i < 5 * 200; i++) { step(stepPin); }

  delay(500);

  // Negative direction
  digitalWrite(axisPin, LOW);
  for (int i = 0; i < 5 * 200; i++) { step(stepPin); }
}

bool XYPlotterController::testX() {
  testMotor(PIN_X_DIRECTION, PIN_X_STEP);
  return true;
}

bool XYPlotterController::testY() {
  testMotor(PIN_Y_DIRECTION, PIN_Y_STEP);
  return true;
}
} // namespace calebrjc::XYPlotter
