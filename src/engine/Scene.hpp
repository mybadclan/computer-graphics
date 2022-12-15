#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "../shapes/Ray.hpp"
#include "../shapes/Sphere.hpp"

#include "../lightSource/LS.hpp"
#include "../lightSource/AmbientLS.hpp"
#include "../lightSource/PontualLS.hpp"
#include "../lightSource/DirectionalLS.hpp"
#include "../lightSource/SpotLS.hpp"


class Scene {
  private:
    Ray ray_;
    std::vector<Shape*> shapes_;

    AmbientLS* ambientLS_;
    PontualLS* pontualLS_;
    DirectionalLS* directionalLS_;
    SpotLS* spotLS_;

    bool isAmbientOn_ = false;
    bool isPontualOn_ = false;
    bool isSpotOn_ = false;
    bool isDirectionalOn_ = false;
    bool isOrthogonal_ = false;

    bool hasShadow_(PontualLS* ls, Vector p);

  public:
    Scene();
    Scene(Ray ray);

    void setAmbientLS(AmbientLS* ambientLS);
    void setPontualLS(PontualLS* pontualLS);
    void setDirectionalLS(DirectionalLS* directionalLS);
    void setSpotLS(SpotLS* spotLS);

    void toggleAmbient();
    void togglePontual();
    void toggleSpot();
    void toggleDirectional();
    void toggleOrthogonalVision();

    std::vector<Shape*> getShapes();
    Ray getRay();

    void push(Shape* shape);

    Color paint(Vector origin, Vector coord);
};

#endif