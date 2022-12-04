#include "Face.hpp"

Face::Face() {
  p0_ = 0;
  p1_ = 0;
  p2_ = 0;
}

Face::Face(int p0, int p1, int p2) {
  p0_ = p0;
  p1_ = p1;
  p2_ = p2;
}

void Face::getPoints(int* p0, int* p1, int* p2) {
  *p0 = p0_;
  *p1 = p1_;
  *p2 = p2_;
}