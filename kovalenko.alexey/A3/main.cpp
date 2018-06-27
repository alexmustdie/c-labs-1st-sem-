#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace kovalenko;

int main()
{
  try
  {
    auto rectangle = std::make_shared<Rectangle>(point_t{0, 0}, 20, 10);
    std::cout << "rectangle was created\n\n";

    rectangle->printData();

    auto circle = std::make_shared<Circle>(point_t{10, 10}, 10);
    std::cout << "\ncircle was created\n\n";

    circle->printData();

    CompositeShape composite_shape(rectangle);
    std::cout << "\ncomposite shape was created\n\n"
      << "rectangle was added to composite shape\n";

    composite_shape.addShape(circle);
    std::cout << "circle was added to composite shape\n\n";

    (&composite_shape)->printData();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
