#ifndef TRIANGLE_HPP_INCLUDED
#define TRIANGLE_HPP_INCLUDED
#include "shape.hpp"

class Triangle:
  public Shape
{
public:
  Triangle(const point_t &pos_a, const point_t &pos_b, const point_t &pos_c);
  point_t getCenter() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void printFeatures() const override;
  void move(double dx, double dy) override;
  void move(const point_t &pos) override;

private:
  point_t corners_[3];
};

#endif
