#include <cmath>
#include <math.h>
#include <iostream>

#include "Matrix.hpp"

Matrix::Matrix() {
  for (int i=0; i < 4; i+=1) {
    for (int j=0; j < 4; j+=1) {
      m[i][j] = i == j ? 1 : 0;
    }
  }
}

int Matrix::size() {
  return 4;
}

float& Matrix::operator () (int i, int j) {
  return m[i][j];
}

Matrix Matrix::operator * (Matrix other) {
  Matrix res;

  for (int i=0; i<size();i+=1) {
    for (int j=0; j<size(); j+=1) {
      for(int k=0; k<size(); k+=1) {
        res(i, j) += (*this)(i, k) * other(j, k);
      }
    }
  }

  return res;
}

Vector Matrix::operator *(Vector other) {
  float ox, oy, oz;
  other.getXYZ(&ox, &oy, &oz);

  float x = m[0][0] * ox + m[0][1] * oy + m[0][2] * oz + m[0][3];
  float y = m[1][0] * ox + m[1][1] * oy + m[1][2] * oz + m[1][3];
  float z = m[2][0] * ox + m[2][1] * oy + m[2][2] * oz + m[2][3];

  return Vector(x, y, z);
}

Matrix Matrix::translate(float tx, float ty, float tz) {
  Matrix matrix = Matrix();

  matrix(0, 3) = tx;
  matrix(1, 3) = ty;
  matrix(2, 3) = tz;

  return matrix;
}

Matrix Matrix::scale(float sx, float sy, float sz) {
  Matrix matrix = Matrix();

  matrix(0, 0) = sx;
  matrix(1, 1) = sy;
  matrix(2, 2) = sz;

  return matrix;
}

// pi ---> 180
// x  ---> teta
// x = pi * teta / 180

Matrix Matrix::rotateX(float teta) {
  float radians = (M_PI * teta) / 180;

  Matrix matrix = Matrix();

  float c = std::cos(radians);
  float s = std::sin(radians);

  matrix(1, 1) = c;
  matrix(1, 2) = -s;
  matrix(2, 1) = s;
  matrix(2, 2) = c;

  return matrix;
}

Matrix Matrix::rotateY(float teta) {
  float radians = (M_PI * teta) / 180;

  Matrix matrix = Matrix();

  float c = std::cos(radians);
  float s = std::sin(radians);

  matrix(0, 0) = c;
  matrix(0, 2) = s;
  matrix(2, 0) = -s;
  matrix(2, 2) = c;

  return matrix;
}

Matrix Matrix::rotateZ(float teta) {
  float radians = (M_PI * teta) / 180;

  Matrix matrix = Matrix();

  float c = std::cos(radians);
  float s = std::sin(radians);

  matrix(0, 0) = c;
  matrix(0, 1) = -s;
  matrix(1, 0) = s;
  matrix(1, 1) = c;

  return matrix;
}

Matrix Matrix::reflectXY() {
  Matrix matrix = Matrix();
  matrix(2, 2) = -1;

  return matrix;
}

Matrix Matrix::reflectYZ() {
  Matrix matrix = Matrix();
  matrix(0, 0) = -1;

  return matrix;
}

Matrix Matrix::reflectXZ() {
  Matrix matrix = Matrix();
  matrix(1, 1) = -1;

  return matrix;
}

Matrix Matrix::skewXY(float gama) {
  float radians = (M_PI * gama) / 180;
  float t = std::tan(radians);

  Matrix matrix = Matrix();
  matrix(1, 0) = t;

  return matrix;
}

Matrix Matrix::skewYZ(float gama) {
  float radians = (M_PI * gama) / 180;
  float t = std::tan(radians);

  Matrix matrix = Matrix();
  matrix(2, 1) = t;

  return matrix;
}

Matrix Matrix::skewZY(float gama) {
  float radians = (M_PI * gama) / 180;
  float t = std::tan(radians);

  Matrix matrix = Matrix();
  matrix(1, 2) = t;

  return matrix;
}

Matrix Matrix::skewXZ(float gama) {
  float radians = (M_PI * gama) / 180;
  float t = std::tan(radians);

  Matrix matrix = Matrix();
  matrix(2, 0) = t;

  return matrix;
}

Matrix Matrix::skewZX(float gama) {
  float radians = (M_PI * gama) / 180;
  float t = std::tan(radians);

  Matrix matrix = Matrix();
  matrix(0, 2) = t;

  return matrix;
}

void Matrix::print() {
  for (int i=0; i < 4; i+=1) {
    for (int j=0; j < 4; j+=1) {
      std::cout << m[i][j] << " ";
    }

    std::cout << std::endl;
  }
}
