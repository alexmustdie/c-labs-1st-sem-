#ifndef MATRIXSHAPE_HPP_INCLUDED
#define MATRIXSHAPE_HPP_INCLUDED
#include "shape.hpp"
#include <memory>

namespace kovalenko
{
  class MatrixShape
  {
  public:
    MatrixShape(const std::shared_ptr<Shape> &);
    MatrixShape(const MatrixShape &);
    MatrixShape(MatrixShape &&);
    MatrixShape & operator=(const MatrixShape &);
    MatrixShape & operator=(MatrixShape &&);
    std::unique_ptr <std::shared_ptr<Shape>[]>::pointer operator[](size_t index) const;
    void addShape(const std::shared_ptr<Shape> &);
    void print() const noexcept;

  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> matrix_;
    size_t rows_, columns_;
    bool checkOverlap(const std::shared_ptr<Shape> &, const std::shared_ptr<Shape> &) const noexcept;
  };
}

#endif
