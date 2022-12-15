#include "Recipient.hpp"
#include "Plane.hpp"
#include <cmath>

Recipient::Recipient(): Shape(Model()) {
  props_ = ShapeConfig();
}

Recipient::Recipient(ShapeConfig props): Shape(Model()) {
  props_ = props;
}

Recipient::Recipient(ShapeConfig props, Model model): Shape(model) {
  props_ = props;
}

bool Recipient::inShell_(Vector other) {
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  double height = props_.getHeight();
  double aux = (other - centerBase).dotProduct(&direction);
  return aux >= 0 && aux <= height;
}

bool Recipient::inBase_(Vector other, bool top) {
  Vector centerBase = props_.getCenterBase();
  Vector direction = props_.getDirection();
  double height, radius;
  props_.getScalarProps(&height, &radius);

  Vector centerTop = centerBase + (direction * height);

  Vector c = top ? centerTop : centerBase;
  double size = (other - c).norm();

  return size <= radius;
}

Vector Recipient::calcN_(Vector other) {
  Vector direction = props_.getDirection();
  Vector centerBase = props_.getCenterBase();

  Vector cp = other - centerBase;
  Vector ca = direction * (cp).dotProduct(&direction);

  return (cp - ca).normalized();
}

ShapeConfig Recipient::getProps() {
  return props_;
}

void Recipient::pushShape(Shape* shape) {
  shapes_.push_back(shape);
}

Vector Recipient::surfaceNormal(Vector other) {
  return n_;
}

bool Recipient::intersectsCylinder_(Vector origin, Vector coord) {
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

bool Recipient::intersects(Vector origin, Vector coord) {
  if (intersectsCylinder_(origin, coord)) {
    vector<int> ts;

    for(int i=0; i<(int)shapes_.size(); i+=1) {
      Shape* shape = shapes_.at(i);

      if (shape->intersects(origin, coord)) {
        ts.push_back(i);
      }
    }

    if (ts.size() == 0) return false;

    int minPos = ts.at(0);
    Shape* shapeMin = shapes_.at(minPos);

    double tMin;
    shapeMin->getTMin(&tMin);

    for (int i=1;i<(int)ts.size();i+=1) {
      int pos = ts.at(i);
      Shape* shape = shapes_.at(pos);

      double t;
      shape->getTMin(&t);

      if (t < tMin) {
        tMin = t;
        shapeMin = shape;
      }
    }

    setTMin(tMin);
    return true;
  }

  return false;
}

void Recipient::transform(Matrix matrix, TransformType tType) {

}