#include "matrix-shape.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace kovalenko;

MatrixShape::MatrixShape(const std::shared_ptr<Shape> &shape):
  matrix_(new std::shared_ptr<Shape>[1]),
  rows_(1),
  columns_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }

  matrix_[0] = shape;
}

MatrixShape::MatrixShape(const MatrixShape &matrix_shape):
  rows_(matrix_shape.rows_),
  columns_(matrix_shape.columns_)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> matrix_copy(new std::shared_ptr<Shape>[rows_ * columns_]);
  
  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    matrix_copy[i] = matrix_shape.matrix_[i];
  }
  
  matrix_.swap(matrix_copy);
}

MatrixShape::MatrixShape(MatrixShape &&matrix_shape):
  rows_(matrix_shape.rows_),
  columns_(matrix_shape.columns_)
{
  matrix_.swap(matrix_shape.matrix_);
}

MatrixShape & MatrixShape::operator=(const MatrixShape &matrix_shape)
{
  if (this != &matrix_shape)
  {
    rows_ = matrix_shape.rows_;
    columns_ = matrix_shape.columns_;
    std::unique_ptr <std::shared_ptr<Shape>[]> matrix_copy(new std::shared_ptr<Shape>[rows_ * columns_]);
    
    for (size_t i = 0; i < (rows_ * columns_); i++)
    {
      matrix_copy[i] = matrix_shape.matrix_[i];
    }
    
    matrix_.swap(matrix_copy);
  }
  
  return *this;
}

MatrixShape & MatrixShape::operator=(MatrixShape &&matrix_shape)
{
  if (this != &matrix_shape)
  {
    rows_ = matrix_shape.rows_;
    columns_ = matrix_shape.columns_;
    matrix_.swap(matrix_shape.matrix_);
  }

  return *this;
}

std::unique_ptr <std::shared_ptr<Shape>[]>::pointer MatrixShape::operator[](size_t index) const
{
  if (index > rows_)
  {
    throw std::invalid_argument("index out of range");
  }

  return matrix_.get() + index * columns_;
}

void MatrixShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }

  size_t i = rows_ * columns_;
  size_t desired_row = 1; // номер строки, на которую будет помещена фигура

  while (i > 0)
  {
    i--;

    if (checkOverlap(matrix_[i], shape))
    {
      desired_row = i / columns_ + 2;
    }
  }

  size_t rows_temp = rows_;
  size_t columns_temp = columns_;
  size_t free_columns = 0; // число свободных ячеек на выбранной строке

  if (desired_row > rows_)
  {
    rows_temp++;
    free_columns = columns_;
  }
  else
  {
    size_t j = (desired_row - 1) * columns_;

    while (j < (desired_row * columns_))
    {
      if (matrix_[j] == nullptr)
      {
        free_columns++;
      }

      j++;
    }
    
    if (free_columns == 0)
    {
      columns_temp++;
      free_columns = 1;
    }
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> matrix_temp(new std::shared_ptr<Shape>[rows_temp * columns_temp]);
  
  for (size_t i = 0; i < rows_temp; i++)
  {
    for (size_t j = 0; j < columns_temp; j++)
    {
      if (i >= rows_ || j >= columns_)
      {
        matrix_temp[i * columns_temp + j] = nullptr;
        continue;
      }

      matrix_temp[i * columns_temp + j] = matrix_[i * columns_ + j];
    }
  }

  matrix_temp[desired_row * columns_temp - free_columns] = shape;
  
  matrix_.swap(matrix_temp);
  rows_ = rows_temp;
  columns_ = columns_temp;
}

bool MatrixShape::checkOverlap(const std::shared_ptr<Shape> &shape_1, const std::shared_ptr<Shape> &shape_2) const noexcept
{
  if (shape_1 == nullptr || shape_2 == nullptr)
  {
    return false;
  }

  rectangle_t shape_1_frame_rect = shape_1->getFrameRect();
  rectangle_t shape_2_frame_rect = shape_2->getFrameRect();

  return ((abs(shape_1_frame_rect.pos.x - shape_2_frame_rect.pos.x)
    < ((shape_1_frame_rect.width / 2) + (shape_2_frame_rect.width / 2)))
    && ((abs(shape_1_frame_rect.pos.y - shape_2_frame_rect.pos.y)
    < ((shape_1_frame_rect.height / 2) + (shape_2_frame_rect.height / 2)))));
}

void MatrixShape::print() const noexcept
{
  for (size_t i = 0; i < rows_; i++)
  {
    for (size_t j = 0; j < columns_; j++)
    {
      if (matrix_[i * columns_ + j] != nullptr)
      {
        std::cout << std::setw(16) << std::left << matrix_[i * columns_ + j]->getName();
      }
    }

    std::cout << "\n";
  }
}
