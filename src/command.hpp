// File: command_info.hpp
// Author(s): Caleb Johnson-Cantrell

#ifndef XYPLOTTER_COMMAND_INFO_HPP_
#define XYPLOTTER_COMMAND_INFO_HPP_

namespace calebrjc::XYPlotter {
// Max size for instruction labels.
const size_t MAX_INSTRUCTION_LENGTH = 4;

// Number of parameters needed to fulfill the longest instruction.
const size_t MAX_PARAMETER_COUNT = 4;

// Commands are comprised of an instruction and related parameters, defined below.
// Format: INST-0-1-2-3 where 0, 1, 2 and 3 represent instruction parameters
typedef struct {
  char instruction[MAX_INSTRUCTION_LENGTH + 1];
  size_t numParameters;
  size_t *parameters[MAX_PARAMETER_COUNT];
} Command;

// Commands:

// Turn off - TOFF
// Usage: TOFF-DNC-DNC-DNC-DNC
// Ex: 0000-0-0-0-0
const char *COMMAND_TURN_OFF = "TOFF";

// Home pen - HOME
// Usage: HOME-X(bool)-Y(bool)-DNC-DNC
// Ex: HOME-1-1-0-0
const char *COMMAND_HOME = "HOME";

// Pen up/down - MPEN
// Usage: MPEN-Up/Down(bool)-DNC-DNC-DNC
// Ex: MPEN-1-0-0-0
const char *COMMAND_MOVE_PEN = "MPEN";

// Move to coordinates - MOVE
// Usage: MOVE-A(X1)-B(Y1)-C(X2)-D(Y2)
// Ex: MOVE-18-32-94-67
const char *COMMAND_MOVE = "MOVE";

// Draw line - DRLN
// Usage: DRLN-A(X1)-B(Y1)-C(X2)-D(Y2)
// Ex: DRLN-18-32-94-67
const char *COMMAND_DRAW_LINE = "DRLN";

// Draw rectangle - DRRT
// Usage: DRRT-A(X1)-B(Y1)-C(X2)-D(Y2)
// Ex: DRRT18-32-94-67
// Note: (X1, Y1) = top left, (X2, Y2) = bottom right
const char *COMMAND_DRAW_RECT = "DRRT";

// Set Speed - STSD
// Usage: STSD-Axis(0=X,1=Y)-Speed(int)-DNC-DNC
// Ex: STSD-1-2957-0-0
// Note: A <= Speed <= B
const char *COMMAND_SET_SPEED = "STSD";

// Set vertical position - STVP
// Usage: STVP-Axis(0=x,1=Y)-Position(int)
// Ex: STVP-1-2957-0-0
// Note: A <= Speed <= B
const char *COMMAND_SET_VPOS = "STVP";
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_ARDUINO_FIRMWARE_HPP_