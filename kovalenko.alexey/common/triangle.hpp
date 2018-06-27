#ifndef TRIANGLE_HPP_INCLUDED
#define TRIANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace kovalenko
{
  class Triangle:
    public Shape
  {
  public:
    Triangle(const point_t &, const point_t &, const point_t &);
    friend bool kovalenko::operator==(const Triangle &, const Triangle &) noexcept;
    point_t getCenter() const noexcept;
    std::string getName() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printFeatures() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t &pos) noexcept override;
    void scale(double k) override;
    void rotate(double angle) noexcept override;

  private:
    point_t corners_[3];
  };

  bool operator==(const Triangle &, const Triangle &) noexcept;
}

#endif
