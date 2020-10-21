// File: xy_plotter_controller.hpp
// Author(s): Caleb Johnson-Cantrell

#ifndef XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_
#define XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_

#include "command.hpp"

namespace calebrjc::XYPlotter {
class XYPlotterController {
 public:
  XYPlotterController(size_t xSpeed, size_t ySpeed, size_t penUpPos, size_t penDownPos);
  ~XYPlotterController();
  bool executeCommand(const Command& command);

 private:
  bool penIsUp;
  size_t maxSpeedX;
  size_t maxSpeedY;
  size_t penUpPos;
  size_t penDownPos;
  bool turnOff(void);
  bool home(bool x, bool y);
  bool move(size_t x, size_t y);
  bool drawLine(size_t x1, size_t y1, size_t x2, size_t y2);
  bool drawRectangle(size_t x1, size_t y1, size_t x2, size_t y2);
  bool setMotorSpeed(bool x, size_t speed);
  bool setPenPosition(bool up, long);
};  // XYPlotterController
}  // namespace calebrjc::XYPlotter

#endif  // XYPLOTTER_XY_PLOTTER_CONTROLLER_HPP_