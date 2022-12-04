#ifndef RAY_HPP
#define RAY_HPP

#include "../math/Vector.hpp"
#include "../utils/Color.hpp"

class Ray {
  private:
    Vector camera_;
    Color bgColor_;

  public:
    Ray();
    Ray(Vector camera, Color bgColor);

    Vector getCamera();
    Color getBgColor();
};

#endif