#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "../shapes/Ray.hpp"
#include "../shapes/Sphere.hpp"
#include "../lightSource/LS.hpp"

class Scene {
  private:
    Ray ray_;
    std::vector<Shape*> shapes_;
    std::vector<LS*> lightSources_;

    void verify_sphere();

  public:
    Scene();
    Scene(Ray ray);


    std::vector<Shape*> getShapes();
    std::vector<LS*> getLightSources();
    Ray getRay();

    void push(Shape* shape);
    void pushLightSource(LS* ls);

    Color paint(Vector origin, Vector coord);
};

#endif