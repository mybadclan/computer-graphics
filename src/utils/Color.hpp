#ifndef COLOR_HPP
#define COLOR_HPP

#include "../math/Vector.hpp"

class Color {
  private:
    int r_, g_, b_;

  public:

    Color();

    Color(int r, int g, int b);

    int getR();
    int getG();
    int getB();
    void getRGB(int* r, int* g, int* b);

    Color operator * (double alpha);
    Color operator * (Vector other);
    Color operator * (Color other);

    void print();
};

#endif