#ifndef COMPOSITESHAPE_HPP_INCLUDED
#define COMPOSITESHAPE_HPP_INCLUDED
#include "shape.hpp"
#include <memory>

namespace kovalenko
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> &);
    CompositeShape(const CompositeShape &);
    CompositeShape(CompositeShape &&);
    CompositeShape & operator=(const CompositeShape &);
    CompositeShape & operator=(CompositeShape &&);
    friend bool kovalenko::operator==(const CompositeShape &, const CompositeShape &) noexcept;
    void addShape(const std::shared_ptr<Shape> &);
    std::string getName() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void printFeatures() const noexcept override {};
    void move(double dx, double dy) noexcept override;
    void move(const point_t &pos) noexcept override;
    void scale(double k) override;
    void rotate(double angle) noexcept override;

  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
  };

  bool operator==(const CompositeShape &, const CompositeShape &) noexcept;
}

#endif
