#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  void printData() const;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void printFeatures() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void move(const point_t &pos) = 0;
};

#endif
