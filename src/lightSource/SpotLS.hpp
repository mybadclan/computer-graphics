#ifndef SPOT_LS_HPP
#define SPOT_LS_HPP

#include "LS.hpp"

class SpotLS: public LS {
  private:
    Vector position_;
    Vector direction_;
    Vector is_;
    double teta_;

  public:
    SpotLS();
    SpotLS(Vector position, Vector direction, Vector is, double teta);
    // SpotLS(Vector position, Vector direction, Vector is, Vector id, Vector ie, double teta);

    virtual Vector iluminate(Vector pI, Vector d, Vector n, Model model) override;
};

#endif