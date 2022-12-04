#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "../shapes/Ray.hpp"
#include "../shapes/Sphere.hpp"

class Scene {
  private:
    Ray ray_;
    std::vector<Shape*> shapes_;

    void verify_sphere();

  public:
    Scene();
    Scene(Ray ray);


    std::vector<Shape*> getShapes();
    Ray getRay();

    void push(Shape* shape);

    Color paint(Vector origin, Vector coord);
};

#endif