#ifndef SHAPE_CONFIG_HPP
#define SHAPE_CONFIG_HPP

#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"

#include "../shapes/Shape.hpp"

class ShapeConfig {
  private:
    Vector centerBase_;
    Vector direction_;
    float height_;
    float radius_;

  public:
    ShapeConfig();
    ShapeConfig(Vector centerBase, Vector direction, float height, float radius);

    Vector getCenterBase();
    Vector getDirection();
    float getHeight();
    float getRadius();
    void getScalarProps(float* height, float* radius);

    void transform(Matrix matrix, TransformType tType);
};

#endif