#include <iostream>
#include <cmath>
#include "Sphere.hpp"

Sphere::Sphere(): Shape() {
  center_ = Vector();
  radius_ = 1;
  model_ = Model();
}

Sphere::Sphere(Vector center, float radius, Model model): Shape(model) {
  center_ = center;
  radius_ = radius;
}

Vector Sphere::getCenter() {
  return center_;
}

float Sphere::getRadius() {
  return radius_;
}

Vector Sphere::surfaceNormal(Vector other) {
  return (other - center_) / radius_;
}

bool Sphere::isValid() {
  return true;
}

bool Sphere::intersects(Vector origin, Vector coord) {
  Vector w = origin - center_;

  Vector d = (coord - origin).normalized();

  // a = 1
  float b = 2*d.dotProduct(&w);
  float c = w.dotProduct(&w) - std::pow(radius_, 2);
  float delta = std::pow(b, 2) - 4*c;

  if (delta < 0) return false;

  float sqrtDelta = std::sqrt(delta);

  float t1 = (-b + sqrtDelta) / 2;
  float t2 = (-b - sqrtDelta) / 2;
  float tMin = std::min(t1, t2);

  if (tMin > 0.0001f) {
    Shape::setTMin(tMin);
    return true;
  }

  return false;
}

void Sphere::transform(Matrix matrix, TransformType t_type) {
  switch (t_type) {
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
