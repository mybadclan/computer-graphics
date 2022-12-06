#include "Cylinder.hpp"
#include "Plane.hpp"
#include <cmath>
#include <limits>
#include <iostream>

Cylinder::Cylinder(): Shape(Model()) {
  hit_ = SURFACE;
  props_ = ShapeConfig();
}

Cylinder::Cylinder(ShapeConfig props): Shape(Model()) {
  hit_ = SURFACE;
  props_ = props;
}

Cylinder::Cylinder(ShapeConfig props, Model model): Shape(model) {
  hit_ = SURFACE;
  props_ = props;
}


bool Cylinder::inShell_(Vector other) {
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  double height = props_.getHeight();
  double aux = (other - centerBase).dotProduct(&direction);
  return aux >= 0 && aux <= height;
}

bool Cylinder::inBase_(Vector other, bool top) {
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  double height, radius;
  props_.getScalarProps(&height, &radius);

  Vector centerTop = centerBase + (direction * height);

  Vector c = top ? centerTop : centerBase;
  double size = (other - c).norm();

  return size <= radius;
}

Vector Cylinder::calcN_(Vector other) {
  Vector direction = props_.getDirection();
  Vector centerBase = props_.getCenterBase();

  Vector cp = other - centerBase;
  Vector ca = direction * (cp).dotProduct(&direction);

  return (cp - ca).normalized();
}

ShapeConfig Cylinder::getProps() {
  return props_;
}

Vector Cylinder::surfaceNormal(Vector other) {
  return n_;
}

bool Cylinder::intersects(Vector origin, Vector coord) {
  double height, radius;
  props_.getScalarProps(&height, &radius);

  Vector direction = props_.getDirection();
  Vector centerBase = props_.getCenterBase();
  Vector centerTop  = centerBase + (direction * height);

  Vector d = (coord - origin).normalized();

  Vector v = (origin - centerBase) - (direction * (origin - centerBase).dotProduct(&direction));
  Vector w = d - (direction * d.dotProduct(&direction));

  double a = w.dotProduct(&w);
  double b = v.dotProduct(&w);
  double c = v.dotProduct(&v) - (radius*radius);
  double delta = b*b - a*c;

  if (delta < 0) {
    return false;
  }

  double sqrtDelta = std::sqrt(delta);
  double t1 = (-b + sqrtDelta) / a;
  double t2 = (-b - sqrtDelta) / a;

  Vector p1 = origin + (d * t1);
  Vector p2 = origin + (d * t2);

  if (inShell_(p1) && inShell_(p2) && delta > 0) {
    double t = t1 < t2 ? t1 : t2;
    Vector pI = t1 < t2 ? p1 : p2;

    if (t > 0) {
      n_ = calcN_(pI);
      setTMin(t);
      return true;
    }
  }

  double tMin;

  if (inShell_(p1)) tMin = t1;
  if (inShell_(p2) && t2 < tMin) tMin = t2;

  bool intersectBase = false;

  Plane planeBase { centerBase, direction * -1 };
  Plane planeTop  { centerTop, direction };

  if (planeBase.intersects(origin, coord)) {
    double t;
    planeBase.getTMin(&t);

    Vector pI = origin + (d * t);
    bool auxIntersect = inBase_(pI, false);
    if (t > 0 && t < tMin && auxIntersect) {
      tMin = t; n_ = direction * -1; intersectBase = auxIntersect;
    }
  }

  if (planeTop.intersects(origin, coord)) {
    double t;
    planeTop.getTMin(&t);

    Vector pI = origin + (d * t);
    bool auxIntersect = inBase_(pI, true);
    if (t > 0 && t < tMin && auxIntersect) {
      tMin = t; n_ = direction; intersectBase = auxIntersect;
    }
  }

  if (intersectBase) {
    setTMin(tMin);
    return true;
  }

  Vector pI = origin + (d*tMin);

  if (tMin > 0 && inShell_(pI)) {
    n_ = calcN_(pI);
    setTMin(tMin);
    return true;
  }

  return false;
}

void Cylinder::transform(Matrix matrix, TransformType tType) {

}
