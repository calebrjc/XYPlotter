// File: command_interface.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the class defined in command_parser.hpp.

#include "command_parser.hpp"

namespace calebrjc::XYPlotter {

Command CommandParser::queue() {
  char *data = this->getRawData();
  Command command = this->convertToCommand(data);

  return command;
}  // CommandParser::queue

char *CommandParser::getRawData() {
  // Code goes here.
  return nullptr;
}  // CommandParser::getRawData

Command CommandParser::convertToCommand(char *data) {
  // Code goes here.
  return Command();
}  // CommandParser::convertToCommand
}  // namespace calebrjc::XYPlotter