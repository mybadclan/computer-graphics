#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

#define SIZE 4

class Matrix {
  private:
    double m[4][4];

  public:
    Matrix();

    int size();

    double& operator () (int i, int j);
    Matrix operator * (Matrix other);
    Vector operator * (Vector other);

    static Matrix translate(double tx, double ty, double tz);
    static Matrix scale(double sx, double sy, double sz);

    static Matrix rotateX(double teta);
    static Matrix rotateY(double teta);
    static Matrix rotateZ(double teta);

    static Matrix reflectXY();
    static Matrix reflectYZ();
    static Matrix reflectXZ();

    static Matrix skewXY(double gama);
    static Matrix skewYZ(double gama);
    static Matrix skewZY(double gama);
    static Matrix skewXZ(double gama);
    static Matrix skewZX(double gama);

    void print();
};

#endif
