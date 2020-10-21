// File: command_parser.hpp
// Author(s): Caleb Johnson-Cantrell

#ifndef XYPLOTTER_COMMAND_PARSER_HPP_
#define XYPLOTTER_COMMAND_PARSER_HPP_

#include "Arduino.h"

#include "command.hpp"

namespace calebrjc::XYPlotter {
class CommandParser {
 public:
  CommandParser();
  ~CommandParser();

  // Retrieves data from the Serial interface defined in Arduino.h and (after some processing and
  // conversion) returns a CommandInfo struct representing a command to be ran on the hardware
  // connected to the Arduino
  Command getCommand() const;
};  // CommandParser
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_COMMAND_PARSER_HPP_