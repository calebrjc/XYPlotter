// File: xy_plotter_controller.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines the XYPlotterController class, the purpose of which is to take an inputted
// Command object (defined in command.hpp) and turn it into low level instructions for the motors
// on the plotter to execute.

#ifndef XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
#define XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_

#include "AccelStepper.h"
#include "Arduino.h"
#include "MultiStepper.h"
#include "Servo.h"
#include "command.hpp"
#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
// Numerical constants
const int PLOTTER_WIDTH = 10000;
const int BACKGROUND_THRESHOLD = 3;
const int FOREGROUND_THRESHOLD = 5;
const int SERVO_UP_POS = 0;    // DEFINE THIS
const int SERVO_DOWN_POS = 0;  // DEFINE THIS

// Analog pins
#define PIN_LIGHT_SENSOR A0
#define PIN_SERVO 0  // DEFINE THIS
#define PIN_X_BUMPERS A1
#define PIN_Y_BUMPERS A2

// Digital pins
const int PIN_ENABLE = 6;
const int PIN_X2_DIRECTION = 7;
const int PIN_X2_STEP = 8;
const int PIN_X1_DIRECTION = 9;
const int PIN_X1_STEP = 10;
const int PIN_Y_DIRECTION = 11;
const int PIN_Y_STEP = 12;
const int PIN_EMERGENCY_STOP = 13;

class XYPlotterController final {
 public:
  // This method initializes the plotter by starting the Serial interface and initializing
  // necessary members such as plotter speed, plotter position, etc and reporting back to
  // the Serial interface with SerialUtil::MESSAGE_READY when initialization is finished.
  void initializePlotter();

  // This method takes the inputted command and attempts to execute it, returning an Arduino String
  // containing SerialUtil::MESSAGE_OKAY or an error description as appropriate, typically based on
  // the result of one of the private execution methods.
  String executeCommand(Command c);

  // Doc
  long xOrigin;

  // Doc
  long yOrigin;

  // Doc
  long yWidth;

  // Doc
  long xWidth;

  // Doc
  long xCurrent;

  // Doc
  long yCurrent;

  // Doc
  long targetCoordinates[3];

  // Doc
  AccelStepper xStepper1;

  // Doc
  AccelStepper xStepper2;

  // Doc
  AccelStepper yStepper;

  // Doc
  MultiStepper steppers;

  // Doc
  Servo servo;

  // Doc
  void findPaper();

  // Doc
  long findWidth(char axis);

  // Doc
  long findOrigin(char axis);

  // Doc
  long unscale(long n, char axis);

  // Doc
  void setTargetCoordinates(long x, long y);

  // Doc
  bool isAtTarget();

  // Doc
  bool step();

  // Doc
  bool runToCompletion();

  // Returns true if the plotter is successfully turned off (execution stops and pen is lifted).
  // Note: THIS METHOD DOES NOT END PROGRAM EXECUTION.
  bool turnOff();

  // Returns true if the plotter is successful in testing the motor that controls the X axis.
  bool testX();

  // Returns true if the plotter is successful in testing the motor that controls the Y axis.
  bool testY();

  // Doc
  bool testZ();

  // Doc
  bool penUp();

  // Doc
  bool penDown();

  // Doc
  bool move(long x1, long y1, long x2, long y2);

  // Doc
  bool home();

  // Doc
  bool drawLine(long x1, long y1, long x2, long y2);
};  // XYPlotterController
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
