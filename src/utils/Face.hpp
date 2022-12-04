#ifndef FACE_HPP
#define FACE_HPP

class Face {
  private:
    int p0_;
    int p1_;
    int p2_;

  public:
    Face();
    Face(int p0, int p1, int p2);

    void getPoints(int* p0, int* p1, int* p2);
};

#endif