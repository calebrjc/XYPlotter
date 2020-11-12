// File: command_parser.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines the CommandParser class, the purpose of which is to retrieve data from the
// PC's serial port and convert it into a Command object (defined in command.hpp).

#ifndef XYPLOTTER_COMMAND_PARSER_HPP_
#define XYPLOTTER_COMMAND_PARSER_HPP_

#include "Arduino.h"

#include "command.hpp"
#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
class CommandParser final {
 public:
  // Returns a Command structure constructed with data gathered from the Serial interface that the
  // Arduino is connected to by making the CommandParser block execution until sufficient data
  // arrives, and processing the data when its ready.
  Command queue();

 private:
  // Loads formatted data into o_data, using raw data gathered from the Serial interface.
  //
  // Input data format: 4-character instruction string and up to 4
  // 4-chracter hex numbers, for a max of 20 bytes.
  // Ex: INST270F1E61
  //
  // Output data format: Same as the raw data format, but with
  // dashes inserted between blocks to make parsing easier.
  // Ex: INST-270F-1E61
  void getProcessedData(char *o_data);

  // Returns a Command structure that has been filled with information gleaned from the buffer that
  // is passed in, presumably one made from a call to getRawData().
  //
  // For example, if this method is called with the data used in getProcessedData's example, the
  // following statements should be true, given that the returned Command was stored in a variable
  // named command:
  //
  // command.instruction = "INST"
  // command.numParameters = 2
  // command.parameters = {270F, 1E61}
  Command convertToCommand(char *data);
}; // CommandParser
} // namespace calebrjc::XYPlotter

#endif // XYPLOTTER_COMMAND_PARSER_HPP_
