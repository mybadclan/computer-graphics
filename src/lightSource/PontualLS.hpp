#ifndef PONTUAL_LS_HPP
#define PONTUAL_LS_HPP

#include "./LS.hpp"

class PontualLS: public LS {
  private:
    Vector position_;

  public:
    PontualLS(Vector position, Vector id, Vector ie, Vector ia);
    PontualLS(Vector position, Vector i);

    Vector getPosition();

    virtual Vector iluminate(Vector pI, Vector d, Vector n, Model model) override;
};

#endif

