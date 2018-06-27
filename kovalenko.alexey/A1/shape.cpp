#include <iostream>
#include "shape.hpp"

void Shape::printData() const
{
  printFeatures();

  rectangle_t frame_rect = getFrameRect();

  std::cout << "area: " << getArea() << "\n"
    << "framing rectangle:\n"
    << "  x: " << frame_rect.pos.x << "\n"
    << "  y: " << frame_rect.pos.y << "\n"
    << "  width: " << frame_rect.width << "\n"
    << "  height: " << frame_rect.height << "\n";
}
