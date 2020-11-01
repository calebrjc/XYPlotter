// File: xy_plotter_controller.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the class defined in xy_plotter_controller.hpp.

#include "xy_plotter_controller.hpp"

namespace calebrjc::XYPlotter {
// String constants for command names.

void XYPlotterController::initializePlotter() {
  Serial.begin(9600);
  while (!Serial) { } // Halt execution until the serial interface is ready
}  // XYPlotterController::initializePlotter()

void XYPlotterController::executeCommand(Command c) {
  bool result = false;

  if (strcmp(c.instruction, COMMAND_TURN_OFF)) {
    result = this->turnOff();
  }  // if

  if (result) SerialUtil::sendMessage(SerialUtil::MESSAGE_OK);
  else SerialUtil::sendMessage(SerialUtil::MESSAGE_ERROR);
}  // XYPlotterController::executeCommand()

bool XYPlotterController::turnOff() {
  // Code goes here.
  return false;
}  // XYPlotterController::turnOff
}  // namespace calebrjc::XYPlotter
