// File: command_info.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines a structure names Command that stores information about instructions that need
// to be given to the motors and their parameters. Constants to define sizes that have to do with
// commands will also be located in this file.

#ifndef XYPLOTTER_INSTRUCTION_INFO_HPP_
#define XYPLOTTER_INSTRUCTION_INFO_HPP_

#include "Arduino.h"

namespace calebrjc::XYPlotter {
// Numerical constants
const size_t MAX_BUFFER_SIZE = 64;        // bytes
const size_t MAX_INSTRUCTION_LENGTH = 4;  // characters
const size_t MAX_NUM_PARAMETERS = 4;      // integers

// String constants
//
// Note: These constants use the "#define" preprocessor macro instead of the "const char *" type in
// order to avoid multiple definition complications.
#define COMMAND_TURN_OFF "TOFF"

struct Command final {
  char instruction[MAX_INSTRUCTION_LENGTH + 1];  // 5 bytes
  int numParameters;                             // 8 bytes
  long int parameters[MAX_NUM_PARAMETERS];       // 32 bytes
};  // Command                                   // Total = 45 bytes
}  // namespace calebrjc::XYPlotter
#endif  // XYPLOTTER_ARDUINO_FIRMWARE_HPP_
