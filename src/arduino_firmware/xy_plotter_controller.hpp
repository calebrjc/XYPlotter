// File: xy_plotter_controller.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines the XYPlotterController class, the purpose of which is to take an inputted
// Command object (defined in command.hpp) and turn it into low level instructions for the motors
// on the plotter to execute.

#ifndef XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
#define XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_

#include "Arduino.h"
#include "command.hpp"
#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
// Pin constants
const int PIN_X_DIRECTION = 9;
const int PIN_X_STEP      = 10;
const int PIN_Y_DIRECTION = 11;
const int PIN_Y_STEP      = 12;

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

 private:
  // Returns true if the plotter is successfully turned off (execution stops and pen is lifted).
  // Note: THIS METHOD DOES NOT END PROGRAM EXECUTION.
  bool turnOff();

  // Returns true if the plotter is successful in testing the motor that controls the X axis.
  bool testX();

  // Returns true if the plotter is successful in testing the motor that controls the Y axis.
  bool testY();
}; // XYPlotterController
} // namespace calebrjc::XYPlotter

#endif // XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
