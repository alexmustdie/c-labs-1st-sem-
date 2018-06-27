#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace kovalenko;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape):
  shapes_(new std::shared_ptr<Shape>[1]),
  size_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }

  shapes_[0] = shape;
}

CompositeShape::CompositeShape(const CompositeShape &composite_shape):
  size_(composite_shape.size_)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> shapes_copy(new std::shared_ptr<Shape>[size_]);
  
  for (size_t i = 0; i < size_; i++)
  {
    shapes_copy[i] = composite_shape.shapes_[i];
  }
  
  shapes_.swap(shapes_copy);
}

CompositeShape::CompositeShape(CompositeShape &&composite_shape):
  size_(composite_shape.size_)
{
  shapes_.swap(composite_shape.shapes_);
}

CompositeShape & CompositeShape::operator=(const CompositeShape &composite_shape)
{
  if (this != &composite_shape)
  {
    size_ = composite_shape.size_;
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_copy(new std::shared_ptr<Shape>[size_]);
    
    for (size_t i = 0; i < size_; i++)
    {
      shapes_copy[i] = composite_shape.shapes_[i];
    }
    
    shapes_.swap(shapes_copy);
  }
  
  return *this;
}

CompositeShape & CompositeShape::operator=(CompositeShape &&composite_shape)
{
  if (this != &composite_shape)
  {
    size_ = composite_shape.size_;
    shapes_.swap(composite_shape.shapes_);
  }

  return *this;
}

bool kovalenko::operator==(const CompositeShape &composite_shape_1, const CompositeShape &composite_shape_2) noexcept
{
  if (composite_shape_1.size_ != composite_shape_2.size_)
  {
    return false;
  }

  size_t i = 0;

  while (i < composite_shape_1.size_)
  {
    if (composite_shape_1.shapes_[i] == composite_shape_2.shapes_[i])
    {
      i++;
    }
    else
    {
      return false;
    }
  }

  return true;
}

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> shapes_temp(new std::shared_ptr<Shape>[size_ + 1]);
  
  for (size_t i = 0; i < size_; i++)
  {
    shapes_temp[i] = shapes_[i];
  }
  
  shapes_temp[size_] = shape;
  size_++;
  shapes_.swap(shapes_temp);
}

std::string CompositeShape::getName() const noexcept
{
  return "composite shape";
}

double CompositeShape::getArea() const noexcept
{
  double area = shapes_[0]->getArea();

  for (size_t i = 1; i < size_; i++)
  {
    area += shapes_[i]->getArea();
  }

  return area;
}

rectangle_t CompositeShape::getFrameRect() const noexcept
{
  rectangle_t shape_frame_rect = shapes_[0]->getFrameRect();

  double shape_frame_rect_top_left_x = shape_frame_rect.pos.x - shape_frame_rect.width / 2;
  double shape_frame_rect_top_left_y = shape_frame_rect.pos.y + shape_frame_rect.height / 2;
  
  double shape_frame_rect_bottom_right_x = shape_frame_rect.pos.x + shape_frame_rect.width / 2;
  double shape_frame_rect_bottom_right_y = shape_frame_rect.pos.y - shape_frame_rect.height / 2;
  
  point_t top_left = {shape_frame_rect_top_left_x, shape_frame_rect_top_left_y};
  point_t bottom_right = {shape_frame_rect_bottom_right_x, shape_frame_rect_bottom_right_y};

  for (size_t i = 1; i < size_; i++)
  {
    shape_frame_rect = shapes_[i]->getFrameRect();

    shape_frame_rect_top_left_x = shape_frame_rect.pos.x - shape_frame_rect.width / 2;
    shape_frame_rect_top_left_y = shape_frame_rect.pos.y + shape_frame_rect.height / 2;
  
    shape_frame_rect_bottom_right_x = shape_frame_rect.pos.x + shape_frame_rect.width / 2;
    shape_frame_rect_bottom_right_y = shape_frame_rect.pos.y - shape_frame_rect.height / 2;

    if (shape_frame_rect_top_left_x < top_left.x)
    {
      top_left.x = shape_frame_rect_top_left_x;
    }
    
    if (shape_frame_rect_top_left_y > top_left.y)
    {
      top_left.y = shape_frame_rect_top_left_y;
    }

    if (shape_frame_rect_bottom_right_x > bottom_right.x)
    {
      bottom_right.x = shape_frame_rect_bottom_right_x;
    }
    
    if (shape_frame_rect_bottom_right_y < bottom_right.y)
    {
      bottom_right.y = shape_frame_rect_bottom_right_y;
    }
  }

  point_t center = {(top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2};

  return {center, bottom_right.x - top_left.x, top_left.y - bottom_right.y};
}

void CompositeShape::move(double dx, double dy) noexcept
{ 
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t &pos) noexcept
{
  point_t center = getFrameRect().pos; 
  move(pos.x - center.x, pos.y - center.y);
}

void CompositeShape::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("invalid scaling factor");
  }

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t shape_center = shapes_[i]->getFrameRect().pos;
    
    shapes_[i]->move({center.x + k * (shape_center.x - center.x),
      center.y + k * (shape_center.y - center.y)});
    
    shapes_[i]->scale(k);
  }
}

void CompositeShape::rotate(double angle) noexcept
{
  double angle_cos = cos(angle * M_PI / 180);
  double angle_sin = sin(angle * M_PI / 180);

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t shape_center = shapes_[i]->getFrameRect().pos;

    shapes_[i]->move({center.x + angle_cos * (shape_center.x - center.x) - angle_sin * (shape_center.y - center.y),
      center.y + angle_cos * (shape_center.y - center.y) + angle_sin * (shape_center.x - center.x)});

    shapes_[i]->rotate(angle);
  }
}
