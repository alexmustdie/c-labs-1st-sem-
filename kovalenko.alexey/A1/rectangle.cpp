#include <iostream>
#include <cassert>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t &pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  assert(width_ > 0 && height_ > 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::printFeatures() const
{
  std::cout << "x: " << pos_.x << "\n"
    << "y: " << pos_.y << "\n"
    << "width: " << width_ << "\n"
    << "height: " << height_ << "\n";
}

void Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}
