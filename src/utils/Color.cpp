#include <algorithm>
#include <iostream>
#include "Color.hpp"

Color::Color() {
  r_ = 100;
  g_ = 100;
  b_ = 100;
}

Color::Color(int r, int g, int b) {
  r_ = std::min(std::max(0, r), 255);
  g_ = std::min(std::max(0, g), 255);
  b_ = std::min(std::max(0, b), 255);
}

int Color::getR() {
  return r_;
}

int Color::getG() {
  return g_;
}

int Color::getB() {
  return b_;
}

void Color::getRGB(int* r, int* g, int* b) {
  *r = r_;
  *g = g_;
  *b = b_;
}

Color Color::operator *(double alpha) {
  return Color(r_*alpha, g_*alpha, b_*alpha);
}

Color Color::operator *(Vector other) {
  double x, y, z;
  other.getXYZ(&x, &y, &z);

  return Color(r_*x, g_*y, b_*z);
}

Color Color::operator *(Color other) {
  int r, g, b;
  other.getRGB(&r, &g, &b);

  return Color(r_*r, g_*g, b_*b);
}

void Color::print() {
  std::cout << "Color(" << getR() << ", " << getG() << ", " << getB() << ")" << std::endl;
}
