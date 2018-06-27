#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED
#include "base-types.hpp"
#include <string>

namespace kovalenko
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    void printData() const noexcept;
    virtual std::string getName() const noexcept = 0;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void printFeatures() const noexcept = 0;
    virtual void move(double dx, double dy) noexcept = 0;
    virtual void move(const point_t &pos) noexcept = 0;
    virtual void scale(double k) = 0;
    virtual void rotate(double angle) noexcept = 0;
  };
}

#endif
