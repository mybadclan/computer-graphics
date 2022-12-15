#include "AmbientLS.hpp"

AmbientLS::AmbientLS(): LS(Vector()) {}

AmbientLS::AmbientLS(Vector ia): LS(Vector(), Vector(), ia) {}

Vector AmbientLS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  Vector ia;
  getIntensity(&ia);

  Vector ambt = ia * model.getKa();

  return ambt;
}
