#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Window.hpp"
#include "../math/Vector.hpp"

class Canvas {
  private:
    int width_;
    int height_;
    Window window_;

    float dx_;
    float dy_;

  public:
    Canvas(Window window, int width, int height);

    Vector toWindow(Vector worldCoord);

    int getWidth();
    int getHeight();
    float getDx();
    float getDy();

    Window getWindow();

    void print();
};

#endif