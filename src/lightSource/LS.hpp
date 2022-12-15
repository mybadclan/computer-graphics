#ifndef LS_HPP
#define LS_HPP

#include "../math/Vector.hpp"
#include "../utils/Model.hpp"

class LS {
  private:
    Vector id_;
    Vector ie_;
    Vector ia_;

  public:
    LS(Vector id, Vector ie, Vector ia);
    LS(Vector id, Vector ie);
    LS(Vector i);

    void getIntensity(Vector* id, Vector* ie, Vector* ia);
    void getIntensity(Vector* id, Vector* ie);
    void getIntensity(Vector* ia);

    virtual Vector iluminate(Vector pI, Vector d, Vector n, Model model);
};

#endif