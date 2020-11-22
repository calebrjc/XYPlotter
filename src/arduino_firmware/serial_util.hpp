// File: serial_util.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines utility functions to be used when engaging with the Arduino Serial interface.
// These functions require the interface to be initialized, which is done in
// XYPlotterController::initializePlotter().

#ifndef XYPLOTTER_SERIAL_UTIL_HPP_
#define XYPLOTTER_SERIAL_UTIL_HPP_

#include "Arduino.h"

namespace calebrjc::XYPlotter::SerialUtil {
// String constants
//
// Note: These constants use the String type defined in Arduino.h, not to be confused with the
// std::string type defined by the C++ standard library.
const String MESSAGE_READY = "<READY>";
const String MESSAGE_OK    = "<OK>";
const String MESSAGE_ERROR = "<ERROR>";

// This function broadcasts the inputted String via the Serial interface of the Arduino.
void sendMessage(String message);

// This function retrieves raw data from the Serial interface of the Arduino and stores it in the
// inputted char*. As it stands, all incoming messages must be contained within angle brackets
// ('<' and '>') and the string of characters in between them must have a length of 20, for a total
// message length of 22 characters.
void getMessage(char *o_data);
} // namespace calebrjc::XYPlotter::SerialUtil

#endif // XYPLOTTER_SERIAL_UTIL_HPP_
