#include "Plane.hpp"

Plane::Plane(): Shape(Model()) {
  point_ = Vector();
  n_ = Vector();
}

Plane::Plane(Vector point, Vector n): Shape(Model()) {
  point_ = point;
  n_ = n;
}

Plane::Plane(Vector point, Vector n, Model model): Shape(model) {
  point_ = point;
  n_ = n;
}

Vector Plane::surfaceNormal(Vector other) {
  return n_;
}

bool Plane::intersects(Vector origin, Vector coord) {
  Vector w = point_ - origin;
  Vector d = (coord - origin).normalized();

  float wn = w.dotProduct(&n_);
  float dn = d.dotProduct(&n_);

  if (dn != 0.0001f) {
    float t = wn / dn;

    if (t > 0.0001f) {
      Shape::setTMin(wn / dn);
      return true;
    }
  }

  return false;
}

void Plane::transform(Matrix matrix, TransformType type) {

}
