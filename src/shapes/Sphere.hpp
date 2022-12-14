#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"

#include "../utils/Model.hpp"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"

class Sphere: public Shape {
  private:
    Vector center_;
    double radius_;

  public:
    Sphere();
    Sphere(Vector center, double radius, Model model);

    Vector getCenter();
    double getRadius();

    virtual Vector surfaceNormal(Vector other) override;

    virtual bool isValid() override;
    virtual bool intersects(Vector origin, Vector d) override;
    virtual void transform(Matrix matrix, TransformType tType) override;

    void print();
};

#endif
