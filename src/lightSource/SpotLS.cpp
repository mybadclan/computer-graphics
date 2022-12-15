#include "cmath"

#include "SpotLS.hpp"

using namespace std;

SpotLS::SpotLS(): LS(Vector()) {
  position_ = Vector();
  direction_ = Vector();
  teta_ = 1;
}

SpotLS::SpotLS(Vector position, Vector direction, Vector is, double teta): LS(Vector()) {
  position_ = position;
  direction_ = direction;
  teta_ = (M_PI * teta) / 180;
  is_ = is;
}

// SpotLS::SpotLS(Vector position, Vector direction, Vector id, Vector ie, double teta): LS(id, ie) {

// }

Vector SpotLS::iluminate(Vector pI, Vector d, Vector n, Model model) {
  Vector l = (position_ - pI).normalized();

  double cosAlpha = (l * -1.0).dotProduct(&direction_);
  double fAlpha = cosAlpha > cos(teta_) ? cosAlpha : 0.0;

  double ln = l.dotProduct(&n);
  Vector dfs = (is_ * model.getKd()) * std::max(0.0, ln) * fAlpha;

  Vector r = (n * 2 * ln) - l;
  double rv = r.dotProduct(&d);

  double auxMax = std::pow(std::max(0.0, rv), model.getShineness());
  Vector spclr = (is_ * model.getKe()) * auxMax * fAlpha;

  return dfs + spclr;
}