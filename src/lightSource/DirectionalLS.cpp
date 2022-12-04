#include <algorithm>
#include <cmath>
#include "DirectionalLS.hpp"

DirectionalLS::DirectionalLS(Vector direction, Vector id, Vector ie, Vector ia): LS(id, ie, ia), direction_(direction) {}

DirectionalLS::DirectionalLS(Vector direction, Vector i): LS(i), direction_(direction) {}

Color DirectionalLS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  Vector id, ie, ia;
  LS::getIntensity(&id, &ie, &ia);

  Vector ambt = ia * model.getKa();

  Vector l = direction_;
  float ln = l.dotProduct(&n);
  Vector dfs = (id * model.getKd()) * std::max(0.0f, ln);

  Vector r = (n * 2.0f * ln) - l;
  float rv = r.dotProduct(&d);

  float auxMax = std::pow(std::max(0.0f, rv), 2);
  Vector spclr = (ie * model.getKe()) * auxMax;

  return (model.getColor()) * (ambt + dfs + spclr);
}