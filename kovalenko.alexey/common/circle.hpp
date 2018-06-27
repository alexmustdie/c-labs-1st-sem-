#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED
#include "shape.hpp"

namespace kovalenko
{
  class Circle:
    public Shape
  {
  public:
    Circle(const point_t &pos, double radius);
    friend bool kovalenko::operator==(const Circle &, const Circle &) noexcept;
    double getRadius() const noexcept;
    std::string getName() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printFeatures() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t &pos) noexcept override;
    void scale(double k) override;
    void rotate(double /*angle*/) noexcept override {};

  private:
    point_t pos_;
    double radius_;
  };

  bool operator==(const Circle &, const Circle &) noexcept;
}

#endif
