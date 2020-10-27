// File: serial_util.hpp
// Author(s): Caleb Johnson-Cantrell, Jamie (Anny) Ni, Nicholas Bowring, Yongchao Huang
//
// This file defines utility functions to be used when engaging with the Arduino Serial interface.
// These functions require the interface to be initialized, which is done in 
// XYPlotterController::initializePlotter().

#ifndef XYPLOTTER_SERIAL_UTIL_HPP_
#define XYPLOTTER_SERIAL_UTIL_HPP_

#include "Arduino.h"

namespace calebrjc::XYPlotter {
namespace SerialUtil {
// String constants
//
// Note: These constants use the String type defined in Arduino.h, not to be confused with the
// std::string type defined by the C++ standard library.
const String MESSAGE_READY = "READY";
const String MESSAGE_OK = "OK";
const String MESSAGE_ERROR = "ERROR";

// This function broadcasts the inputted String via the Serial interface of the Arduino.
void sendMessage(String message);

// This function retrieves raw data from the Serial interface of the Arduino.
char *getMessage();
}  // namespace SerialUtil
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_SERIAL_UTIL_HPP_