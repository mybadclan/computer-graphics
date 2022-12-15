#ifndef CONE_HPP
#define CONE_HPP

#include "Shape.hpp"
#include "../utils/ShapeConfig.hpp"

class Cone: public Shape {
  private:
    ShapeConfig props_;
    Vector n_;

    Vector calcN_(Vector other);
    bool inShell_(Vector other);
    bool inBase_(Vector other);

  public:
    Cone();
    Cone(ShapeConfig props);
    Cone(ShapeConfig props, Model model);

    ShapeConfig getProps();

    virtual Vector surfaceNormal(Vector other) override;
    virtual bool intersects(Vector origin, Vector d) override;
    virtual void transform(Matrix matrix, TransformType tType) override;
};

#endif