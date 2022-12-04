#ifndef PLANE_HPP
#define PLANE_HPP

#include "./Shape.hpp"

class Plane: public Shape {
  private:
    Vector point_;
    Vector n_;

  public:
    Plane();
    Plane(Vector point, Vector n, Model model);

    virtual Vector surfaceNormal(Vector other) override;
    virtual bool intersects(Vector origin, Vector coord) override;
    virtual void transform(Matrix matrix, TransformType type) override;
};

#endif