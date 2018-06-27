#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace kovalenko;

Circle::Circle(const point_t &pos, double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("invalid_radius");
  }
}

bool kovalenko::operator==(const Circle &circle_1, const Circle &circle_2) noexcept
{
  if (circle_1.pos_.x == circle_2.pos_.x &&
    circle_1.pos_.y == circle_2.pos_.y &&
    circle_1.radius_ == circle_2.radius_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

double Circle::getRadius() const noexcept
{
  return radius_;
}

std::string Circle::getName() const noexcept
{
  return "circle";
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::printFeatures() const noexcept
{
  std::cout << "x: " << pos_.x << "\n"
    << "y: " << pos_.y << "\n"
    << "radius: " << radius_ << "\n";
}

void Circle::move(double dx, double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t &pos) noexcept
{
  pos_ = pos;
}

void Circle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("invalid_scale");
  }
  
  radius_ *= k;
}
