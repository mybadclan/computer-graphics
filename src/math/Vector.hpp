#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>

class Vector {
  private:
    float x_, y_, z_, w_;

  public:

    Vector();
    Vector(float x, float y);
    Vector(float x, float y, float z);
    Vector(float x, float y, float z, float w);

    float getX();
    float getY();
    float getZ();
    float getW();

    void getXYZ(float * x, float * y, float * z);
    void getXYZW(float * x, float * y, float * z, float * w);

    Vector operator + (Vector other);
    Vector operator * (float alpha);
    Vector operator * (Vector other);
    Vector operator - (Vector& other);
    Vector operator / (float alpha);

    float norm();
    float dotProduct(Vector* other);
    Vector crossProduct(Vector* other);

    Vector normalized();

    void print();
};

#endif