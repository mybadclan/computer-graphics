#include <iostream>
#include "Model.hpp"

Model::Model() {
  color_ = Color();
  Vector k = Vector();
  kd_ = ke_ = ka_ = k;
  shineness_ = 1.0f;
}

Model::Model(
  Color color,
  Vector kd,
  Vector ke,
  Vector ka,
  float shineness
) {
  color_ = color;
  kd_ = kd;
  ke_ = ke;
  ka_ = ka;
  shineness_ = shineness;
  texture_ = false;
}

Model::Model(Color color, Vector k, float shineness) {
  color_ = color;
  kd_ = k;
  ke_ = k;
  ka_ = k;
  shineness_ = shineness;
  texture_ = false;
}

Color Model::getColor() {
  return color_;
}

float Model::getShineness() {
  return shineness_;
}

bool Model::hasTexture() {
  return texture_;
}

Vector Model::getKd() {
  return kd_;
}

Vector Model::getKe() {
  return ke_;
}

Vector Model::getKa() {
  return ka_;
}

void Model::print() {
  color_.print();
  kd_.print();
  ke_.print();
  ka_.print();
  
  std::cout << "Shineness(" << shineness_<< ")" << std::endl;
}