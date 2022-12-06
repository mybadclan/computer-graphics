#include "Scene.hpp"

#include <iostream>
#include <vector>

using namespace std;

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
  vector<int> ts;

  for (int i=0; i<(int)shapes_.size(); i+=1) {
    Shape* shape = shapes_.at(i);

    if ((*shape).intersects(origin, coord)) {
      ts.push_back(i);
    }
  }

  if(ts.size() == 0) {
    return Color();
  }

  int minIdx = 0;

  for (int i=1; i<(int)ts.size(); i+=1) {
    double tPos = ts.at(i);
    double tMinPos = ts.at(minIdx);

    double t, tMin;
    
    shapes_.at(tPos)->getTMin(&t);
    shapes_.at(tMinPos)->getTMin(&tMin);

    if (t < tMin) {
      minIdx = i;
    }
  }

  double tMinPos = ts.at(minIdx);
  double tMin;
  
  Shape* shapeMin = shapes_.at(tMinPos);
  shapeMin->getTMin(&tMin);

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
