#include "Scene.hpp"

#include <limits>
#include <iostream>


Scene::Scene() {}

Scene::Scene(Ray ray) {
  ray_ = ray;
}

std::vector<Shape*> Scene::getShapes() {
  return shapes_;
}

Ray Scene::getRay() {
  return ray_;
}

void Scene::push(Shape* shape) {
  shapes_.push_back(shape);
}

Color Scene::paint(Vector origin, Vector coord) {

  // calculating closest shape

  float tMin = std::numeric_limits<float>::max();
  Shape* shapeMin;

  for (int i = 0; i < (int) shapes_.size(); i+=1) {
    Shape* shape = shapes_.at(i);

    if (!(*shape).intersects(origin, coord)) continue;

    float* auxTMin = new float;
    (*shape).getTMin(auxTMin);

    if ((*auxTMin) < tMin) {
      tMin = (*auxTMin);
      shapeMin = shape;
    }
  }

  if (shapeMin == nullptr) {
    return Color(100, 100, 100);
  }

  // calculate shading contribution

  Vector d = (coord - origin).normalized();
  Vector pI = origin + (d * tMin);

  return (*shapeMin).getModel().getColor();
}
