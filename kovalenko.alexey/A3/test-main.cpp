#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace kovalenko;
const double TOLERANCE = 0.0001;

BOOST_AUTO_TEST_SUITE(testCompositeShape)

BOOST_AUTO_TEST_CASE(move_frame_rect_pos)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{0, 0}, 2, 4);
  auto circle = std::make_shared<Circle>(point_t{2, -2}, 2);
  
  CompositeShape composite_shape(rectangle);
  
  composite_shape.addShape(circle);
  composite_shape.move(2, 2);
  
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 3.5, TOLERANCE);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_frame_rect_size)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{2.5, 2}, 3, 2);
  auto circle = std::make_shared<Circle>(point_t{6, 4}, 1);
  
  CompositeShape composite_shape(rectangle);
  
  composite_shape.addShape(circle);
  composite_shape.move({10, 20});
  
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 6, TOLERANCE);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  auto rectangle_1 = std::make_shared<Rectangle>(point_t{1.5, 3}, 3, 1);
  auto rectangle_2 = std::make_shared<Rectangle>(point_t{2.5, 3}, 3, 2);
  
  CompositeShape composite_shape(rectangle_1);
  
  composite_shape.addShape(rectangle_2);
  composite_shape.move({3, 6});
  
  BOOST_CHECK_CLOSE(composite_shape.getArea(), 9, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_frame_rect_pos)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{3, -2}, 2, 2);
  auto circle = std::make_shared<Circle>(point_t{0, 2}, 1);
  
  CompositeShape composite_shape(rectangle);
  
  composite_shape.addShape(circle);
  composite_shape.scale(2);

  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.5, TOLERANCE);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 0, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_frame_rect_size)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{2, -2}, 2, 2);
  auto circle = std::make_shared<Circle>(point_t{-2, 2}, 1);
  
  CompositeShape composite_shape(rectangle);
  
  composite_shape.addShape(circle);
  composite_shape.scale(2);

  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 12, TOLERANCE);
  BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 12, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{-1, 0.5}, 4, 1);
  auto circle = std::make_shared<Circle>(point_t{-2, 3}, 1);
  
  CompositeShape composite_shape(rectangle);
  
  composite_shape.addShape(circle);

  double area = composite_shape.getArea();
  double k = 2;

  composite_shape.scale(k);

  BOOST_CHECK_CLOSE(composite_shape.getArea(), area * k * k, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(invalid_constructor)
{ 
  BOOST_CHECK_THROW(CompositeShape composite_shape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_add_shape)
{
  auto circle = std::make_shared<Circle>(point_t{0, 0}, 3);
  CompositeShape composite_shape(circle);
  
  BOOST_CHECK_THROW(composite_shape.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale)
{
  auto rectangle = std::make_shared<Rectangle>(point_t{0, 0}, 5, 5);
  CompositeShape composite_shape(rectangle);

  BOOST_CHECK_THROW(composite_shape.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
