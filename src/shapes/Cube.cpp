#include "Cube.hpp"

Cube::Cube(): Shape(Model()) {
  vertex_.push_back(Vector(0, 0, 0));
  vertex_.push_back(Vector(0, 0, 1));
  vertex_.push_back(Vector(1, 0, 1));
  vertex_.push_back(Vector(1, 0, 0));
  vertex_.push_back(Vector(0, 1, 0));
  vertex_.push_back(Vector(0, 1, 1));
  vertex_.push_back(Vector(1, 1, 1));
  vertex_.push_back(Vector(1, 1, 0));

  faces_.push_back(Face(5, 1, 6)); // 00
  faces_.push_back(Face(1, 2, 6)); // 01
  faces_.push_back(Face(4, 0, 7)); // 02
  faces_.push_back(Face(7, 0, 3)); // 03
  faces_.push_back(Face(0, 1, 2)); // 04
  faces_.push_back(Face(0, 2, 3)); // 05
  faces_.push_back(Face(4, 5, 6)); // 06
  faces_.push_back(Face(4, 6, 7)); // 07
  faces_.push_back(Face(4, 0, 1)); // 08
  faces_.push_back(Face(4, 1, 5)); // 09
  faces_.push_back(Face(7, 3, 2)); // 10
  faces_.push_back(Face(7, 2, 6)); // 11

  n_ = Vector(0, 0, 1);
}

Cube::Cube(Model model): Shape(model) {
  vertex_.push_back(Vector(0, 0, 0));
  vertex_.push_back(Vector(0, 0, 1));
  vertex_.push_back(Vector(1, 0, 1));
  vertex_.push_back(Vector(1, 0, 0));
  vertex_.push_back(Vector(0, 1, 0));
  vertex_.push_back(Vector(0, 1, 1));
  vertex_.push_back(Vector(1, 1, 1));
  vertex_.push_back(Vector(1, 1, 0));

  faces_.push_back(Face(5, 1, 6)); // 00
  faces_.push_back(Face(1, 2, 6)); // 01
  faces_.push_back(Face(4, 0, 7)); // 02
  faces_.push_back(Face(7, 0, 3)); // 03
  faces_.push_back(Face(0, 1, 2)); // 04
  faces_.push_back(Face(0, 2, 3)); // 05
  faces_.push_back(Face(4, 5, 6)); // 06
  faces_.push_back(Face(4, 6, 7)); // 07
  faces_.push_back(Face(4, 0, 1)); // 08
  faces_.push_back(Face(4, 1, 5)); // 09
  faces_.push_back(Face(7, 3, 2)); // 10
  faces_.push_back(Face(7, 2, 6)); // 11

  n_ = Vector(0, 0, 1);
}

Vector Cube::surfaceNormal(Vector other) {
  return n_;
}

bool Cube::intersects(Vector origin, Vector d) {
  double tMin = std::numeric_limits<double>::max();
  bool intersected = false;
  Vector intersectedNormal = Vector();

  for (int i=0; i < (int) faces_.size(); i+=1) {
    Face face = faces_.at(i);

    int pos0, pos1, pos2;
    face.getPoints(&pos0, &pos1, &pos2);

    Vector p0 = vertex_.at(pos0);
    Vector p1 = vertex_.at(pos1);
    Vector p2 = vertex_.at(pos2);

    Vector r1 = p1 - p0;
    Vector r2 = p2 - p0;
    Vector r1xr2 = r1.crossProduct(&r2);

    Vector n = r1xr2.normalized();
    Plane plane { p0, n, Model() };

    if (plane.intersects(origin, d)) {
      double* auxTMin = new double;
      plane.getTMin(auxTMin);

      Vector pI = origin + (d * (*auxTMin));

      Vector auxP1 = p1 - pI;
      Vector auxP0 = p0 - pI;

      double area = r1xr2.dotProduct(&n);
      double c1 = (p0 - pI).crossProduct(&auxP1).dotProduct(&n) / area;
      double c2 = (p2 - pI).crossProduct(&auxP0).dotProduct(&n) / area;
      double c3 = 1 - c1 - c2;

      if (c1 > 0.0 && c2 > 0.0 && c3 > 0.0 && (*auxTMin) < tMin) {
        intersectedNormal = n;
        tMin = (*auxTMin);
        intersected = true;
      }
    }
  }

  if (intersected) {
    Shape::setTMin(tMin);
    n_ = intersectedNormal;
  }

  return intersected;
}

void Cube::transform(Matrix matrix, TransformType tType) {
  for (int i=0; i<(int)vertex_.size(); i+=1) {
    Vector result = matrix * vertex_.at(i);

    double x, y, z;
    result.getXYZ(&x, &y, &z);
    vertex_.at(i).setXYZ(x, y, z);
  }
}
