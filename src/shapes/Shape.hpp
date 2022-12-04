#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../utils/Model.hpp"
#include "../math/Matrix.hpp"

enum TransformType { TRANSLATE, SCALE, SKEW, REFLECT, ROTATE };

class Shape {
  private:
    Model model_;
    float tMin_;

  public:
    Shape();
    Shape(Model model);

    Model getModel();
    void getTMin(float *tMin);
    void setTMin(float tMin);

    virtual Vector surfaceNormal(Vector other);
    virtual Vector surfaceNormal();

    virtual bool isValid();
    virtual bool intersects(Vector origin, Vector coord);
    virtual void transform(Matrix matrix, TransformType type);

};

#endif