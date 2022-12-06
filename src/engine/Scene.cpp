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

std::vector<LS*> Scene::getLightSources() {
  return lightSources_;
}

Ray Scene::getRay() {
  return ray_;
}

void Scene::push(Shape* shape) {
  shapes_.push_back(shape);
}

void Scene::pushLightSource(LS* ls) {
  lightSources_.push_back(ls);
}

Color Scene::paint(Vector origin, Vector coord) {

  // calculating closest shape

  float tMin = std::numeric_limits<float>::max();
  Shape* shapeMin { nullptr };

  for (int i = 0; i < (int) shapes_.size(); i+=1) {
    Shape* shape = shapes_.at(i);

    if (!(*shape).intersects(origin, coord)) continue;

    float auxTMin;
    (*shape).getTMin(&auxTMin);

    if (auxTMin < tMin) {
      tMin = auxTMin;
      shapeMin = shape;
    }
  }

  if (shapeMin == nullptr) {
    return Color();
  }

  // calculate light source contribution

  Vector d = (coord - origin).normalized();
  Vector pI = origin + (d * tMin);

  Model model = (*shapeMin).getModel();
  Color contributions;

  for (int i=0; i < (int) lightSources_.size(); i+=1) {
    LS* ls = lightSources_.at(i);
    Vector n = (*shapeMin).surfaceNormal(pI);

    contributions = (*ls).iluminate(pI, d, n, model);
  }

  return contributions;
}
