// File: command_interface.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the class defined in command_parser.hpp.

#include "command_parser.hpp"

namespace calebrjc::XYPlotter {
// Numerical constants
const size_t MAX_RAW_DATA_SIZE   = 20; // bytes
const size_t FORMATTED_DATA_SIZE = 25; // bytes

Command CommandParser::queue() {
  char data[FORMATTED_DATA_SIZE + 1];

  this->getProcessedData(data);
  Command command = this->convertToCommand(data);

  return command;
} // CommandParser::queue

void CommandParser::getProcessedData(char *o_data) {
  char data[MAX_RAW_DATA_SIZE + 1];
  SerialUtil::getMessage(data);

  int numDashes = 0;
  for (size_t i = 0; i < FORMATTED_DATA_SIZE; i++) {
    o_data[i] = data[i - numDashes];
    if (i > 0 && (int)i == (5 * (numDashes + 1)) - 1) {
      o_data[i] = '-';
      numDashes++;
    } // if
  }   // for
  o_data[FORMATTED_DATA_SIZE - 1] = '\0';
} // CommandParser::getRawData

int getNumParameters(char *instruction) {
  int numParameters = -1;

  if (strcmp(instruction, COMMAND_TEST) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_TURN_OFF) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_TEST_X) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_TEST_Y) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_TEST_Z) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_PEN_UP) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_PEN_DOWN) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_HOME) == 0) numParameters = 0;
  if (strcmp(instruction, COMMAND_MOVE) == 0) numParameters = 2;
  if (strcmp(instruction, COMMAND_DRAW_LINE) == 0) numParameters = 4;

  return numParameters;
} // getNumParameters

Command CommandParser::convertToCommand(char *data) {
  Command c;

  // Loading c with command data from "data"
  char *token = strtok(data, "-");
  strcpy(c.instruction, token);
  c.numParameters = getNumParameters(c.instruction);
  for (auto i = 0; i < c.numParameters; i++) {
    token           = strtok(nullptr, "-");
    c.parameters[i] = strtoul(token, nullptr, 16);
  } // for

  return c;
} // CommandParser::convertToCommand
} // namespace calebrjc::XYPlotter
