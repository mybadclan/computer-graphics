#ifndef RECIPIENT_HPP
#define RECIPIENT_HPP

#include <vector>

#include "Shape.hpp"
#include "../utils/ShapeConfig.hpp"

using namespace std;

class Recipient: public Shape {
  private:
    ShapeConfig props_;
    Vector n_;
    vector<Shape*> shapes_;

    bool inShell_(Vector other);
    bool inBase_(Vector other, bool top);
    Vector calcN_(Vector other);
    bool intersectsCylinder_(Vector origin, Vector coord);


  public:
    Recipient();
    Recipient(ShapeConfig props);
    Recipient(ShapeConfig props, Model model);


    ShapeConfig getProps();
    void pushShape(Shape* shape);

    virtual Vector surfaceNormal(Vector other) override;
    virtual bool intersects(Vector origin, Vector coord) override;
    virtual void transform(Matrix matrix, TransformType tType) override;
};

#endif