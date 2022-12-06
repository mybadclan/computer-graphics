#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>

class Vector {
  private:
    double x_, y_, z_, w_;

  public:

    Vector();
    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double w);

    double getX();
    double getY();
    double getZ();
    double getW();

    void getXYZ(double * x, double * y, double * z);
    void getXYZW(double * x, double * y, double * z, double * w);

    void setXYZ(double x, double y, double z);
    void setXYZW(double x, double y, double z, double w);

    Vector operator + (Vector other);
    Vector operator * (double alpha);
    Vector operator * (Vector other);
    Vector operator - (Vector other);
    Vector operator / (double alpha);

    double norm();
    double dotProduct(Vector* other);
    Vector crossProduct(Vector* other);

    Vector normalized();

    void print();
};

#endif