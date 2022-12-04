#ifndef DIRECTIONAL_LS_HPP
#define DIRECTIONAL_LS_HPP

#include "./LS.hpp"

class DirectionalLS: public LS {
  private:
    Vector direction_;

  public:
    DirectionalLS(Vector direction, Vector id, Vector ie, Vector ia);
    DirectionalLS(Vector direction, Vector i);

    virtual Color iluminate(Vector pI, Vector d, Vector n, Model model) override;
};

#endif

