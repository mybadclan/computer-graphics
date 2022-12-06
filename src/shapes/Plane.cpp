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

  double wn = w.dotProduct(&n_);
  double dn = d.dotProduct(&n_);

  if (dn != 0.0) {
    double t = wn / dn;

    if (t >= 0.0) {
      Shape::setTMin(t);
      return true;
    }
  }

  return false;
}

void Plane::transform(Matrix matrix, TransformType type) {

}
