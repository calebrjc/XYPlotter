// File: serial_util.cpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file implements the functions defined in serial_util.hpp.

#include "serial_util.hpp"

namespace calebrjc::XYPlotter {
void SerialUtil::sendMessage(String message) {
  // Code goes here.
}  // SerialUtil::sendMessage

char *SerialUtil::getMessage() {
  // Code goes here.
  return (char *)("Hello!");
}  // SerialUtil::getMessage
}  // namespace calebrjc::XYPlotter
