#include <iostream>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

using namespace kovalenko;

int main()
{
  try
  {
    auto rectangle_1 = std::make_shared<Rectangle>(point_t{-1, -2.5}, 6, 3);
    std::cout << "rectangle_1 was created\n\n";

    rectangle_1->printData();

    auto circle = std::make_shared<Circle>(point_t{3, 0}, 3);
    std::cout << "\ncircle was created\n\n";

    circle->printData();

    auto rectangle_2 = std::make_shared<Rectangle>(point_t{-2.5, 1}, 3, 2);
    std::cout << "\nrectangle_2 was created\n\n";

    rectangle_2->printData();

    MatrixShape matrix_shape(rectangle_1);
    std::cout << "\nmatrix was created\n\n";

    matrix_shape.addShape(circle);
    matrix_shape.addShape(rectangle_2);

    matrix_shape.print();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
