#include "LS.hpp"

LS::LS(Vector id, Vector ie, Vector ia): id_(id), ie_(ie), ia_(ia) {}
LS::LS(Vector i): id_(i), ie_(i), ia_(i) {}
LS::LS(Vector id, Vector ie): id_(id), ie_(ie) {}

void LS::getIntensity(Vector* id, Vector* ie, Vector* ia) {
  *id = id_;
  *ie = ie_;
  *ia = ia_;
}

void LS::getIntensity(Vector* id, Vector* ie) {
  *id = id_;
  *ie = ie_;
}

void LS::getIntensity(Vector* ia) {
  *ia = ia_;
}

Vector LS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  return Vector();
}
