#include <cmath>

#include "Cone.hpp"
#include "Plane.hpp"
#include <iostream>

Cone::Cone(): Shape(Model()) {
  props_ = ShapeConfig();
}

Cone::Cone(ShapeConfig props): Shape(Model()) {
  props_ = props;
}

Cone::Cone(ShapeConfig props, Model model): Shape(model) {
  props_ = props;
}

Vector Cone::calcN_(Vector other) {
  double height = props_.getHeight();
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  Vector centerTop = centerBase + (direction * height);

  Vector tp = (centerTop - other);

  return tp
    .crossProduct(&direction)
    .crossProduct(&tp)
    .normalized();
}

bool Cone::inShell_(Vector other) {
  double height = props_.getHeight();
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  Vector centerTop = centerBase + (direction * height);

  double aux = (centerTop - other).dotProduct(&direction);

  return aux >= 0 && aux <= height;
}

bool Cone::inBase_(Vector other) {
  Vector centerBase = props_.getCenterBase();
  double radius = props_.getRadius();
  double size = (other - centerBase).norm();

  return size <= radius;
}

ShapeConfig Cone::getProps() {
  return props_;
}

Vector Cone::surfaceNormal(Vector other) {
  return n_;
}

bool Cone::intersects(Vector origin, Vector d) {
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  double height, radius;
  props_.getScalarProps(&height, &radius);

  Vector centerTop = centerBase + (direction * height);
  Vector v = centerTop - origin;

  double dn = d.dotProduct(&direction);
  double dd = d.dotProduct(&d);
  double vd = v.dotProduct(&d);
  double vn = v.dotProduct(&direction);
  double vv = v.dotProduct(&v);

  double cosTeta = (height * height) / ((height * height) + (radius * radius));

  double a = (dn*dn) - (dd*cosTeta);
  double b = (vd*cosTeta) - (vn*dn);
  double c = (vn*vn) - (vv*cosTeta);
  double delta = b*b - a*c;

  if (delta < 0) {
    return false;
  }

  double sqrtDelta = std::sqrt(delta);
  double t1 = (-b + sqrtDelta) / a;
  double t2 = (-b - sqrtDelta) / a;

  Vector p1 = origin + (d*t1);
  Vector p2 = origin + (d*t2);

  if (inShell_(p1) && inShell_(p2)) {
    double t = t1 < t2 ? t1 : t2;
    Vector pI = t1 < t2 ? p1 : p2;

    if (t > 0) {
      n_ = calcN_(pI); setTMin(t);
      return true;
    }
  }

  double tMin = t1;

  if (inShell_(p2) && t2 < tMin) tMin = t2;

  bool intersectBase = false;
  Plane planeBase { centerBase, direction };

  if (planeBase.intersects(origin, d)) {
    double t;
    planeBase.getTMin(&t);


    Vector pI = origin + (d * t);
    bool auxIntersect = inBase_(pI);
    
    if (t > 0 && auxIntersect) {
      tMin = t; n_ = direction * -1; intersectBase = auxIntersect;
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

void Cone::transform(Matrix matrix, TransformType tType) {

}
