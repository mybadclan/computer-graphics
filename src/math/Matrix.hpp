#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

#define SIZE 4

class Matrix {
  private:
    float m[4][4];

  public:
    Matrix();

    int size();

    float& operator () (int i, int j);
    Matrix operator * (Matrix other);
    Vector operator * (Vector other);

    static Matrix translate(float tx, float ty, float tz);
    static Matrix scale(float sx, float sy, float sz);

    static Matrix rotateX(float teta);
    static Matrix rotateY(float teta);
    static Matrix rotateZ(float teta);

    static Matrix reflectXY();
    static Matrix reflectYZ();
    static Matrix reflectXZ();

    static Matrix skewXY(float gama);
    static Matrix skewYZ(float gama);
    static Matrix skewZY(float gama);
    static Matrix skewXZ(float gama);
    static Matrix skewZX(float gama);

    void print();
};

#endif
