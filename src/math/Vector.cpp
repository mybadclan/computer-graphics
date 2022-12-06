#include <cmath>
#include <iostream>

#include "Vector.hpp"

Vector::Vector() {
  x_ = y_ = z_ = 0;
  w_ = 1;
}

Vector::Vector(double x, double y) {
  x_ = x;
  y_ = y;
  z_ = 0;
  w_ = 1;
}

Vector::Vector(double x, double y, double z) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = 1;
}

Vector::Vector(double x, double y, double z, double w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
}

double Vector::getX() {
  return x_;
}

double Vector::getY() {
  return y_;
}

double Vector::getZ() {
  return z_;
}

double Vector::getW() {
  return w_;
}

void Vector::getXYZ(double * x, double * y, double * z) {
  *x = x_;
  *y = y_;
  *z = z_;
}

void Vector::getXYZW(double * x, double * y, double * z, double * w) {
  *x = x_;
  *y = y_;
  *z = z_;
  *w = w_;
}

void Vector::setXYZ(double x, double y, double z) {
  x_ = x;
  y_ = y;
  z_ = z;
}

void Vector::setXYZW(double x, double y, double z, double w) {
  x_ = x;
  y_ = y;
  z_ = z;
  w_ = w;
}

Vector Vector::operator + (Vector other) {
  double x, y, z;
  other.getXYZ(&x, &y, &z);
  return Vector(x_ + x, y_ + y, z_ + z);
}

Vector Vector::operator * (double alpha) {
  return Vector(x_*alpha, y_*alpha, z_*alpha);
}

Vector Vector::operator*(Vector other) {
  double x, y, z;
  other.getXYZ(&x, &y, &z);
  return Vector(x_*x, y_*y, z_*z);
}

Vector Vector::operator - (Vector other) {
  Vector negativeOther = other * -1;

  return (*this) + negativeOther;
}

Vector Vector::operator / (double alpha) {
  return (*this)*(1/alpha);
}

double Vector::norm() {
  return std::sqrt(dotProduct(this));
}

double Vector::dotProduct(Vector* other) {
  double x, y, z;
  (*other).getXYZ(&x, &y, &z);

  return x_*x + y_*y + z_*z;
}

Vector Vector::crossProduct(Vector* other) {
  double x, y, z;
  (*other).getXYZ(&x, &y, &z);

  return Vector(
    y_*z - z_*y,
    z_*x - x_*z,
    x_*y - y_*x
  );
}


Vector Vector::normalized() {
  double norm = this->norm();

  double x = x_ / norm;
  double y = y_ / norm;
  double z = z_ / norm;

  return Vector(x, y, z);
}

void Vector::print() {
  std::cout << "Vector(" << getX() << ", " << getY() << ", " << getZ() << ")" << std::endl;
}
