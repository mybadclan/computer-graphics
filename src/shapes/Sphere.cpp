#include <iostream>
#include <cmath>
#include "Sphere.hpp"

Sphere::Sphere(): Shape(Model()) {
  center_ = Vector();
  radius_ = 1;
}

Sphere::Sphere(Vector center, double radius, Model model): Shape(model) {
  center_ = center;
  radius_ = radius;
}

Vector Sphere::getCenter() {
  return center_;
}

double Sphere::getRadius() {
  return radius_;
}

Vector Sphere::surfaceNormal(Vector other) {
  return (other - center_) / radius_;
}

bool Sphere::isValid() {
  return true;
}

bool Sphere::intersects(Vector origin, Vector d) {
  Vector w = origin - center_;

  // a = 1
  double b = 2*d.dotProduct(&w);
  double c = w.dotProduct(&w) - std::pow(radius_, 2);
  double delta = std::pow(b, 2) - 4*c;

  if (delta < 0) return false;

  double sqrtDelta = std::sqrt(delta);

  double t1 = (-b + sqrtDelta) / 2;
  double t2 = (-b - sqrtDelta) / 2;
  double tMin = std::min(t1, t2);

  if (tMin > 0.0001) {
    Shape::setTMin(tMin);
    return true;
  }

  return false;
}

void Sphere::transform(Matrix matrix, TransformType tType) {
  switch (tType) {
    case SCALE:
      radius_ *= matrix(0, 0);
      break;
    case ROTATE:
    case SKEW:
      break;
    default:
      center_ = matrix * center_;
      break;
  }
}

void Sphere::print() {
  center_.print();
  std::cout << "Radius(" << radius_ << ")" << std::endl;
}
