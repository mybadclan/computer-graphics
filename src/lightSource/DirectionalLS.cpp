#include <algorithm>
#include <cmath>
#include "DirectionalLS.hpp"

DirectionalLS::DirectionalLS(Vector direction, Vector id, Vector ie, Vector ia): LS(id, ie, ia), direction_(direction) {}

DirectionalLS::DirectionalLS(Vector direction, Vector i): LS(i), direction_(direction) {}

Vector DirectionalLS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  Vector id, ie;
  LS::getIntensity(&id, &ie);

  Vector l = direction_;
  double ln = l.dotProduct(&n);
  Vector dfs = (id * model.getKd()) * std::max(0.0, ln);

  Vector r = (n * 2.0 * ln) - l;
  double rv = r.dotProduct(&d);

  double auxMax = std::pow(std::max(0.0, rv), model.getShineness());
  Vector spclr = (ie * model.getKe()) * auxMax;

  return dfs + spclr;
}