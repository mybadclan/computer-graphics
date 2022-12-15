#ifndef AMBIENT_LS_HPP
#define AMBIENT_LS_HPP

#include "LS.hpp"

class AmbientLS: public LS {
  public:
    AmbientLS();
    AmbientLS(Vector ia);

    virtual Vector iluminate(Vector pI, Vector d, Vector n, Model model) override;
};

#endif