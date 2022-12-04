#ifndef CLOSEST_HPP
#define CLOSEST_HPP

#include "Model.hpp"
#include "../math/Vector.hpp"

class Closest {
  private:
    float* t_;
    Model* model_;
    Vector* normal_;

  public:
    Closest();

    void setVariables(float* t, Model* model, Vector* normal);

    float getT();
    Model getModel();
    Vector getNormal();
};

#endif