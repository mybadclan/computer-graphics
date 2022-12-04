#include "Closest.hpp"

Closest::Closest() {}

void Closest::setVariables(float* t, Model* model, Vector* normal) {
  t_ = t;
  model_ = model;
  normal_ = normal;
}

float Closest::getT() {
  return *t_;
}

Model Closest::getModel() {
  return *model_;
}

Vector Closest::getNormal() {
  return *normal_;
}
