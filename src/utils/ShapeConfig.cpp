#include "ShapeConfig.hpp"

ShapeConfig::ShapeConfig() {
  centerBase_ = Vector();
  direction_ = Vector();
  height_ = 1;
  radius_ = 1;
}

ShapeConfig::ShapeConfig(Vector centerBase, Vector direction, double height, double radius) {
  centerBase_ = centerBase;
  direction_ = direction;
  height_ = height;
  radius_ = radius;
}

Vector ShapeConfig::getCenterBase() {
  return centerBase_;
}

Vector ShapeConfig::getDirection() {
  return direction_;
}

double ShapeConfig::getHeight() {
  return height_;
}

double ShapeConfig::getRadius() {
  return radius_;
}

void ShapeConfig::getScalarProps(double* height, double* radius) {
  *height = height_;
  *radius = radius_;
}

void ShapeConfig::transform(Matrix matrix, TransformType tType) {

}
