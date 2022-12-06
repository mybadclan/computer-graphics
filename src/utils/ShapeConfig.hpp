#ifndef SHAPE_CONFIG_HPP
#define SHAPE_CONFIG_HPP

#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"

#include "../shapes/Shape.hpp"

class ShapeConfig {
  private:
    Vector centerBase_;
    Vector direction_;
    double height_;
    double radius_;

  public:
    ShapeConfig();
    ShapeConfig(Vector centerBase, Vector direction, double height, double radius);

    Vector getCenterBase();
    Vector getDirection();
    double getHeight();
    double getRadius();
    void getScalarProps(double* height, double* radius);

    void transform(Matrix matrix, TransformType tType);
};

#endif