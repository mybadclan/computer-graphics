#ifndef MODEL_HPP
#define MODEL_HPP

#include "Color.hpp"
#include "../math/Vector.hpp"

class Model {
  private:
    Color color_;
    double shineness_; //shineness
    bool texture_;

    Vector kd_;
    Vector ke_;
    Vector ka_;

  public:
    Model();

    Model(
      Color color,
      Vector kd,
      Vector ke,
      Vector ka,
      double shineness
    );

    Model(Color color, Vector k, double shineness);

    Color getColor();
    double getShineness();
    bool hasTexture();

    Vector getKd();
    Vector getKe();
    Vector getKa();

    void print();
};

#endif