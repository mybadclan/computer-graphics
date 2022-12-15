#include <algorithm>
#include <cmath>
#include "PontualLS.hpp"

PontualLS::PontualLS(Vector position, Vector id, Vector ie, Vector ia): LS(id, ie, ia), position_(position) {}

PontualLS::PontualLS(Vector position, Vector i): LS(i), position_(position) {}

Vector PontualLS::getPosition() {
  return position_;
}

Vector PontualLS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  Vector id, ie, ia;

  getIntensity(&id, &ie, &ia);

  // Vector ambt = ia * model.getKa();

  Vector l = (position_ - pI).normalized();
  double ln = l.dotProduct(&n);
  Vector dfs = (id * model.getKd()) * std::max(0.0, ln);

  Vector r = (n * 2 * ln) - l;
  double rv = r.dotProduct(&d);

  double auxMax = std::pow(std::max(0.0, rv), model.getShineness());
  Vector spclr = (ie * model.getKe()) * auxMax;

  return dfs + spclr;
}