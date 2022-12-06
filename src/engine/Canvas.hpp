#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Window.hpp"
#include "../math/Vector.hpp"

class Canvas {
  private:
    int width_;
    int height_;
    Window window_;

    double dx_;
    double dy_;

  public:
    Canvas(Window window, int width, int height);

    Vector toWindow(Vector worldCoord);

    int getWidth();
    int getHeight();
    double getDx();
    double getDy();

    Window getWindow();

    void print();
};

#endif