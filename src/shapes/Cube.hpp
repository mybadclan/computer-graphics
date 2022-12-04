#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>
#include <limits>

#include "./Shape.hpp"
#include "./Plane.hpp"

#include "../utils/Face.hpp"

using namespace std;

class Cube: public Shape {
  private:
    vector<Vector> vertex_;
    vector<Face> faces_;
    Vector n_;

  public:
    Cube();
    Cube(Model model);

    virtual Vector surfaceNormal(Vector other) override;
    virtual bool intersects(Vector origin, Vector coord) override;
    virtual void transform(Matrix matrix, TransformType type) override;
};

#endif