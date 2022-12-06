#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Shape.hpp"
#include "../utils/ShapeConfig.hpp"

enum HitType { SURFACE, BASE, TOP };

class Cylinder: public Shape {
  private:
    HitType hit_;
    ShapeConfig props_;
    Vector n_;

    bool inShell_(Vector other);
    bool inBase_(Vector other, bool top);
    Vector calcN_(Vector other);

  public:
    Cylinder();
    Cylinder(ShapeConfig props);
    Cylinder(ShapeConfig props, Model model);

    ShapeConfig getProps();

    virtual Vector surfaceNormal(Vector other) override;
    virtual bool intersects(Vector origin, Vector coord) override;
    virtual void transform(Matrix matrix, TransformType tType) override;
};

#endif