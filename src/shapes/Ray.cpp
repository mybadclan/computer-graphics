#include "Ray.hpp"

Ray::Ray(): camera_(Vector()), bgColor_(Color()) {};

Ray::Ray(Vector camera, Color bgColor): camera_(camera), bgColor_(bgColor) {};

Vector Ray::getCamera() {
  return camera_;
}

Color Ray::getBgColor() {
  return bgColor_;
}

