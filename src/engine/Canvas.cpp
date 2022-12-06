#include <iostream>
#include "Canvas.hpp"

Canvas::Canvas(Window window, int width, int height) {
  width_ = width;
  height_ = height;
  window_ = window;

  dx_ = (double)window.getWidth() / width;
  dy_ = (double)window.getHeight() / height;
}

Vector Canvas::toWindow(Vector worldCoord) {
  double x, y, z;
  worldCoord.getXYZ(&x, &y, &z);

  double cx = (-window_.getWidth()/2) + (dx_/2) + (dx_*x);
  double cy = (window_.getHeight()/2) - (dy_/2) - (dy_*y);
  double cz = window_.getDistance();

  return Vector(cx, cy, cz);
}

int Canvas::getWidth() {
  return width_;
}

int Canvas::getHeight() {
  return height_;
}

double Canvas::getDx() {
  return dx_;
}

double Canvas::getDy() {
  return dy_;
}

Window Canvas::getWindow() {
  return window_;
}

void Canvas::print() {
  std::cout << "Width(" << width_ << ", " << dx_ << ")" << std::endl;
  std::cout << "Height(" << height_ << "," << dy_ << ")" << std::endl;
  window_.print();
}
