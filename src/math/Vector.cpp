#include <cmath>
#include <iostream>

#include "Vector.hpp"

Vector::Vector() {
  x_ = y_ = z_ = 0;
  w_ = 1;
}

Vector::Vector(float x, float y) {
  x_ = x;
  y_ = y;
  z_ = 0;
  w_ = 1;
}

Vector::Vector(float x, float y, float z) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = 1;
}

Vector::Vector(float x, float y, float z, float w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
}

float Vector::getX() {
  return x_;
}

float Vector::getY() {
  return y_;
}

float Vector::getZ() {
  return z_;
}

float Vector::getW() {
  return w_;
}

void Vector::getXYZ(float * x, float * y, float * z) {
  *x = x_;
  *y = y_;
  *z = z_;
}

void Vector::getXYZW(float * x, float * y, float * z, float * w) {
  *x = x_;
  *y = y_;
  *z = z_;
  *w = w_;
}

void Vector::setXYZ(float x, float y, float z) {
  x_ = x;
  y_ = y;
  z_ = z;
}

void Vector::setXYZW(float x, float y, float z, float w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
}

Vector Vector::operator + (Vector other) {
  float x, y, z;
  other.getXYZ(&x, &y, &z);
  return Vector(x_ + x, y_ + y, z_ + z);
}

Vector Vector::operator * (float alpha) {
  return Vector(x_*alpha, y_*alpha, z_*alpha);
}

Vector Vector::operator*(Vector other) {
  float x, y, z;
  other.getXYZ(&x, &y, &z);
  return Vector(x_*x, y_*y, z_*z);
}

Vector Vector::operator - (Vector other) {
  Vector negativeOther = other * -1;

  return (*this) + negativeOther;
}

Vector Vector::operator / (float alpha) {
  return (*this)*(1/alpha);
}

float Vector::norm() {
  return std::sqrt(dotProduct(this));
}

float Vector::dotProduct(Vector* other) {
  float x, y, z;
  (*other).getXYZ(&x, &y, &z);

  return x_*x + y_*y + z_*z;
}

Vector Vector::crossProduct(Vector* other) {
  float x, y, z;
  (*other).getXYZ(&x, &y, &z);

  return Vector(
    y_*z - z_*y,
    z_*x - x_*z,
    x_*y - y_*x
  );
}


Vector Vector::normalized() {
  float norm = this->norm();

  float x = x_ / norm;
  float y = y_ / norm;
  float z = z_ / norm;

  return Vector(x, y, z);
}

void Vector::print() {
  std::cout << "Vector(" << getX() << ", " << getY() << ", " << getZ() << ")" << std::endl;
}
