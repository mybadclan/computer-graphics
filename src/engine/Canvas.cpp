#include <iostream>
#include "Canvas.hpp"

Canvas::Canvas(Window window, int width, int height) {
  width_ = width;
  height_ = height;
  window_ = window;

  dx_ = (float)window.getWidth() / width;
  dy_ = (float)window.getHeight() / height;
}

Vector Canvas::toWindow(Vector worldCoord) {
  float x, y, z;
  worldCoord.getXYZ(&x, &y, &z);

  float cx = (-window_.getWidth()/2) + (dx_/2) + (dx_*x);
  float cy = (window_.getHeight()/2) - (dy_/2) - (dy_*y);
  float cz = window_.getDistance();

  return Vector(cx, cy, cz);
}

int Canvas::getWidth() {
  return width_;
}

int Canvas::getHeight() {
  return height_;
}

float Canvas::getDx() {
  return dx_;
}

float Canvas::getDy() {
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
