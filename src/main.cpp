
#include <iostream>

#include "./engine/SDLEngine.h"
#include "engine/Window.hpp"
#include "engine/Canvas.hpp"
#include "engine/Scene.hpp"

#include "math/Vector.hpp"
#include "math/Matrix.hpp"

#include "lightSource/PontualLS.hpp"

#include "utils/Model.hpp"
#include "utils/Color.hpp"

#include "shapes/Shape.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Ray.hpp"

#define WIDTH_SCREEN 500
#define HEIGHT_SCREEN 500
#define WIDTH_CANVAS 500
#define HEIGHT_CANVAS 500

// HEIGHT_CANVAS * WIDTH_CANVAS * 3
#define CANVAS_ARRAY_SIZE 500 * 500

using namespace std;

int main() {
  SDLEngine sdlEngine{
    "Trabalho CG",
    WIDTH_SCREEN,
    HEIGHT_SCREEN,
    WIDTH_CANVAS,
    HEIGHT_CANVAS
  };

  Color pixels[CANVAS_ARRAY_SIZE];
  SDL_Event e;
  bool quit = false;

  for (int i = 0; i < CANVAS_ARRAY_SIZE; i++)
    pixels[i] = Color();

  Window window { 60, 60, -30 };
  Canvas canvas { window, WIDTH_CANVAS, HEIGHT_CANVAS };
  Ray ray { Vector(0, 0, 0), Color(100, 100, 100) };
  Scene scene { ray };

  Model m1 {
    Color { 255, 0, 0 },
    Vector { 0.7, 0.7, 0.7 },
    10.0f
  };

  Model m2 {
    Color { 0, 255, 0 },
    Vector { 0.6, 0.6, 0.6 },
    12.0f
  };

  Model m3 {
    Color { 0, 0, 255 },
    Vector { 0.5, 0.5, 0.5 },
    13.0f
  };

  Sphere sphere1 { Vector(0, 0, -100), 10, m1 };
  Sphere sphere2 { Vector(0, 0, -120), 15, m2 };
  Sphere sphere3 { Vector(0, 0, -150), 15, m3 };

  scene.push(&sphere1);
  scene.push(&sphere2);
  scene.push(&sphere3);

  PontualLS ls1 { Vector(-100, 140, -20), Vector(0.7, 0.7, 0.7) };

  Vector origin = Vector();
  Vector d = Vector(0, 0, -30);

  scene.paint(origin, d).print();

  // while (!quit)
  // {
  //   while (SDL_PollEvent(&e))
  //   {
  //     if (e.type == SDL_QUIT)
  //       quit = true;
  //   }

  //   for (int x = 0; x < WIDTH_CANVAS; x+=1) {
  //     for (int y = 0; y < HEIGHT_CANVAS; y+=1) {
  //       Vector windowCoord = canvas.toWindow(Vector(x, y));
  //       Vector origin = scene.getRay().getCamera();

  //       if (sphere1.intersects(origin, windowCoord)) {
  //         Color color = sphere1.getModel().getColor();

  //         int pos = x + (HEIGHT_CANVAS * y);

  //         pixels[pos] = color;
  //       }
  //     }
  //   }

  //   sdlEngine.atualizarCanvas((int *)pixels);
  //   sdlEngine.atualizarJanela();
  // }

  return 0;
}
