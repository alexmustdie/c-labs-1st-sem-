#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace kovalenko
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);
    friend bool kovalenko::operator==(const Rectangle &, const Rectangle &) noexcept;
    double getWidth() const noexcept;
    double getHeight() const noexcept;
    std::string getName() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printFeatures() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t &pos) noexcept override;
    void scale(double k) override;
    void rotate(double angle) noexcept override;

  private:
    point_t corners_[4];
    double width_, height_;
  };

  bool operator==(const Rectangle &, const Rectangle &) noexcept;
}

#endif
