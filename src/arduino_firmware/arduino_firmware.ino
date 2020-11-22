// File: arduino_firmware.ino
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file serves as the entry point to this application. It utilizes the
// calebrjc::XYPlotter::CommandParser and calebrjc::XYPlotter::XYPlotterController classes to fetch
// data from the Serial interface, interpret them as commands, provide the necessary
// instructions to the motors to complete the command, and send an acknowledgement message via the
// Serial interface.
//
// Current list of supported commands:
// TOFF . . . . . . . . Put the hardware in a safe state (pen up, not moving, at home, etc.)
// TSTX . . . . . . . . Test the motor that controls the X axis by producing 3 rotations in the
//                      positive and negative directions
// TSTY . . . . . . . . Test the motor that controls the Y axis by producing 3 rotations in the
//                      positive and negative directions

#include "Arduino.h"

#include "command_parser.hpp"
#include "serial_util.hpp"
#include "xy_plotter_controller.hpp"

// A CommandParser object, defined in command_parser.hpp
auto cp = calebrjc::XYPlotter::CommandParser();

// A XYPlotterController object, defined in xy_plotter_controller.hpp
auto xypc = calebrjc::XYPlotter::XYPlotterController();

// Initialization code
void setup() {
  xypc.initializePlotter();
} // setup

// Main function that does the real work of this program
void loop() {
  calebrjc::XYPlotter::Command c = cp.queue();
  String acknowledgement         = xypc.executeCommand(c);
  calebrjc::XYPlotter::SerialUtil::sendMessage(acknowledgement);
} // loop
