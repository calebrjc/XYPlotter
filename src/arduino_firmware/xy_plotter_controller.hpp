// File: xy_plotter_controller.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines the XYPlotterController class, the purpose of which is to take an inputted
// Command object (defined in command.hpp) and turn it into low level instructions for the motors
// on the plotter to execute.

#ifndef XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
#define XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_

#include "command.hpp"
#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
// Pin constants
const int PIN_X_STEP = 7;
const int PIN_X_DIRECTION = 8;
const int PIN_Y_STEP = 9;
const int PIN_Y_DIRECTION = 10;

class XYPlotterController final {
 public:
  // This method initializes the plotter by starting the Serial interface and initializing
  // necessary members such as plotter speed, plotter position, etc and reporting back to
  // the Serial interface with SerialUtil::MESSAGE_READY when initialization is finished.
  void initializePlotter();

  // This method takes the inputted command and attempts to execute it, reporting back to the
  // serial with either SerialUtil::MESSAGE_OK or SerialUtil::MESSAGE_ERROR as appropriate,
  // typically based on the result of one of the private execution methods.
  void executeCommand(Command c);

 private:
  // Returns true if the plotter is successfully turned off.
  // Note: THIS METHOD DOES NOT END PROGRAM EXECUTION.
  bool turnOff();
};  // XYPlotterController
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_