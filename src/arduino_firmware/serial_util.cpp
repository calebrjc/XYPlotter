// File: serial_util.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the functions defined in serial_util.hpp.

#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
void SerialUtil::sendMessage(String message) {
  Serial.print(message);
} // SerialUtil::sendMessage

void SerialUtil::getMessage(char *o_data) {
  bool reading = true, recording = false;
  char c;
  while (reading) {
    if (Serial.available() <= 0) continue; // Wait until serial data is available

    c = Serial.read();

    if (recording) {
      if (c == '>') { reading = false; }
      if (reading) (*o_data++) = c;
    } // if
    if (c == '<') recording = true;
  } // while
  *o_data = '\0';
} // SerialUtil::getMessage
} // namespace calebrjc::XYPlotter
