#include "Shape.hpp"

Shape::Shape() {
  model_ = Model();
}

Shape::Shape(Model model) {
  model_ = model;
}

Model Shape::getModel() {
  return model_;
}

void Shape::getTMin(double* tMin) {
  *tMin = tMin_;
}

void Shape::setTMin(double tMin) {
  tMin_ = tMin;
}

Vector Shape::surfaceNormal(Vector other) {
  return Vector();
}

bool Shape::isValid() {
  return true;
}

bool Shape::intersects(Vector origin, Vector coord) {
  return false;
}

void Shape::transform(Matrix matrix, TransformType tType) {}

