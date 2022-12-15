#include "Scene.hpp"

#include <iostream>
#include <vector>

using namespace std;

Scene::Scene() {}

Scene::Scene(Ray ray) {
  ray_ = ray;
}

bool Scene::hasShadow_(PontualLS* ls, Vector p) {
  Vector d = (ls->getPosition() - p).normalized();
  vector<int> ts;

  for (int i=0; i<(int)shapes_.size(); i+=1) {
    Shape* shape = shapes_.at(i);

    if ((*shape).intersects(p, d)) {
      ts.push_back(i);
    }
  }

  if(ts.size() == 0) {
    return false;
  }

  return true;
}

void Scene::setAmbientLS(AmbientLS* ambientLS) {
  ambientLS_ = ambientLS;
}

void Scene::setPontualLS(PontualLS* pontualLS) {
  pontualLS_ = pontualLS;
}

void Scene::setDirectionalLS(DirectionalLS* directionalLS) {
  directionalLS_ = directionalLS;
}

void Scene::toggleAmbient() {
  isAmbientOn_ = !isAmbientOn_;
}

void Scene::togglePontual() {
  isPontualOn_ = !isPontualOn_;
}

void Scene::toggleDirectional() {
  isDirectionalOn_ = !isDirectionalOn_;
}

void Scene::toggleOrthogonalVision() {
  isOrthogonal_ = !isOrthogonal_;
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
  Vector O = isOrthogonal_ ? coord : origin;
  Vector d = isOrthogonal_ ? Vector(0, 0, -1) : (coord - origin).normalized();

  // calculating closest shape
  vector<int> ts;

  for (int i=0; i<(int)shapes_.size(); i+=1) {
    Shape* shape = shapes_.at(i);

    if ((*shape).intersects(O, d)) {
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

  Vector pI = origin + (d * tMin);

  Model model = (*shapeMin).getModel();
  Vector contributions = Vector();

  Vector n = (*shapeMin).surfaceNormal(pI);
  
  if (isAmbientOn_) {
    contributions = contributions + ambientLS_->iluminate(pI, d, n, model);
  }

  if (isPontualOn_) {
    contributions = contributions + pontualLS_->iluminate(pI, d, n, model);
  }

  if (isDirectionalOn_) {
    contributions = contributions + directionalLS_->iluminate(pI, d, n, model);
  }

  return model.getColor() * contributions;
}
