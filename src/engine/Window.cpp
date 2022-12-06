#include <iostream>

#include "Window.hpp"

Window::Window() {
  width_ = 100;
  height_ = 100;
  distance_ = -20;
}

Window::Window(int width, int height, double distance) {
  width_ = width;
  height_ = height;
  distance_ = distance;
}

int Window::getWidth() {
  return width_;
}

int Window::getHeight() {
  return height_;
}

double Window::getDistance() {
  return distance_;
}

void Window::print() {
  std::cout << "Window(" << width_ << ", " << height_ << ", " << distance_ << ")" << std::endl;
}