#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../utils/Model.hpp"
#include "../math/Matrix.hpp"

enum TransformType { TRANSLATE, SCALE, SKEW, REFLECT, ROTATE, MIX };

class Shape {
  private:
    Model model_;
    double tMin_;

  public:
    Shape();
    Shape(Model model);

    Model getModel();
    void getTMin(double *tMin);
    void setTMin(double tMin);

    virtual Vector surfaceNormal(Vector other);

    virtual bool isValid();
    virtual bool intersects(Vector origin, Vector coord);
    virtual void transform(Matrix matrix, TransformType tType);

};

#endif