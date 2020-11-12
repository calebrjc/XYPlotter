# XYPlotter

Software for an Arduino CNC machine, built for UGA's ELEE 4230 course in fall 2020.

## Overview

### arduino_firmware
Execution begins in `arduino_firmware.h`, where the hardware is initialized by `XYPlotter::initializePlotter()` in `setup()` and `CommandParser::queue()` is called in the beginning of `loop()`. `queue()` calls `CommandParser::getProcessedData()`.

`getProcessedData()` calls `SerialUtil::getMessage()`, which makes the Arduino halt until a `<` is encountered in the serial buffer, at which point it will begin to read data from the serial buffer until a `>` is encountered. The data between the `<` and `>` *must* be a sequence of alphanumeric characters with a length of 20, where the first four characters are alpha and the rest are numeric. After retrieving the raw data, `getProcessedData()` formats it with dash separators to make parsing easier, and then `queue()` calls `CommandParser::convertToCommand()` to translate the formatted data into a `Command` object, (defined in `command.hpp`).

Once a `Command` is obtained, `loop()` will call `XYPlotterController::executeCommand()`, which will match the `Command`'s instruction with one of our predefined instructions and calls the corresponding private function and returning a string that signifies the result of the operation (`SerialUtil::MESSAGE_OK` or `SerialUtil::MESSAGE_ERROR`). `loop()` then emits this message across the serial port.

### frontend_program
Execution begins in `main.py` where a `SerialCommunicator` (defined in `modules/serial_communication.py`) object is constructed, setting up communication with the COM port the the Arduino resides on (this will have to be changed depending on the port that the Arduino is on, more on that in a future update). The program then prompts the user for a command to run, and the `interpret_command()` function handles the work of parsing the command, asking for additional information as needed and sending the command data over the serial port in the format specified in the `arduino_firmware` section.


## Changelog
- **27 October 2020**:
  - This is commit hash `a7348b9` and what I consider to be the starting point of this code. All following changelog entries start from here.

- **31 October 2020**:
  - `command.hpp`
    - The data type of `Command::numParameters` has been changed from `size_t` to `int` to allow this size to take a value of -1 for error checking purposes.
    - The data type of `Command::parameters` has been changed from `int[]` to `long int[]` to fit the return type of functions used to gather its values, namely `strtol()` from the `string.h` header of the C library.
  - `serial_util.hpp` and `serial_util.cpp`
    - All functions defined in `serial_util.hpp` have been implemented in `serial_util.cpp`.
    - `SerialUtil::getMessage()` is now void and accepts a `char*` as an output parameter. This is done so that programmers are not forced to delete memory returned by the function.
  - `command_parser.hpp` and `command_parser.cpp`
    - All functions defined in `command_parser.hpp` have been implemented in `command_parser.cpp`.
    - `CommandParser::getRawData()` has been renamed to `CommandParser::getProcessedData()` for semantic reasons. `CommandParser` doesn't need to get raw data when `SerialUtil::getMessage()` already does. It just takes the raw data and transforms it into usable data.
    - `CommandParser::getProcessedData()` is now `void` and accepts a `char*` as an output parameter for the same reason that `SerialUtil::getMessage()` was changed.
  - `xy_plotter_controller.cpp`
    -  `XYPlotterController::initializePlotter()` has been given a basic implementation.

- **12 November 2020**:
  - Added the changes necessary to implement the `TSTX` and `TSTY` commands (string constants, `strcmp()` calls, declaration in `xy_plotter_controller.hpp`, implementation in `xy_plotter_controller.cpp`).
  - Added the frontend program.
  - Overview section is up!
