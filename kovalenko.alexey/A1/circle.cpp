#include <iostream>
#include <cassert>
#include <cmath>
#include "circle.hpp"

Circle::Circle(const point_t &pos, double radius):
  pos_(pos),
  radius_(radius)
{
  assert(radius_ > 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::printFeatures() const
{
  std::cout << "x: " << pos_.x << "\n"
    << "y: " << pos_.y << "\n"
    << "radius: " << radius_ << "\n";
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}
