
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
#include "utils/ShapeConfig.hpp"

#include "shapes/Shape.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"
#include "shapes/Cube.hpp"
#include "shapes/Cylinder.hpp"
#include "shapes/Ray.hpp"

#define WIDTH_CANVAS 800
#define HEIGHT_CANVAS 800

// HEIGHT_CANVAS * WIDTH_CANVAS * 3
#define CANVAS_ARRAY_SIZE HEIGHT_CANVAS * WIDTH_CANVAS

using namespace std;

int main() {
  SDLEngine sdlEngine{
    "Trabalho CG",
    WIDTH_CANVAS,
    HEIGHT_CANVAS,
    WIDTH_CANVAS,
    HEIGHT_CANVAS
  };

  Color pixels[CANVAS_ARRAY_SIZE];
  SDL_Event event;
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
    10.0
  };

  Model m2 {
    Color { 0, 255, 0 },
    Vector { 0.6, 0.6, 0.6 },
    12.0
  };

  Model m3 {
    Color { 0, 0, 255 },
    Vector { 0.5, 0.5, 0.5 },
    13.0
  };

  Sphere sphere1 { Vector(0, 0, -100), 10, m1 };
  Sphere sphere2 { Vector(0, 0, -120), 15, m2 };
  Sphere sphere3 { Vector(0, 0, -150), 15, m3 };

  Plane plane1 { Vector(0, -50, 0), Vector(0, 1, 0), m2 };

  Vector nTest = Vector(0, 50, -50) - Vector(0, -20, -100);

  ShapeConfig sc1 { Vector(0, -40, -100), Vector(0, 1, 0), 80, 20 };
  Cylinder cylinder1 { sc1, m3 };

  Cube cube1 { m1 };
  Cube cube2 { m1 };
  Cube cube3 { m2 };
  Cube cube4 { m1 };

  Matrix auxM1 = Matrix::translate(0, -50, -100) * Matrix::scale(10, 10, 10) * Matrix::rotateY(45);
  Matrix auxM2 = Matrix::translate(-20, -50, -100) * Matrix::scale(10, 10, 10);
  Matrix auxM3 = Matrix::translate(20, -50, -100) * Matrix::scale(10, 10, 10) * Matrix::rotateY(45);
  Matrix auxM4 = Matrix::translate(0, 20, -100) * Matrix::scale(10, 10, 10);

  cube1.transform(auxM1, SCALE);
  cube2.transform(auxM2, SCALE);
  cube3.transform(auxM3, SCALE);
  cube4.transform(auxM4, SCALE);

  scene.push(&sphere1);
  scene.push(&cylinder1);
  scene.push(&plane1);
  scene.push(&cube1);
  scene.push(&cube2);
  scene.push(&cube3);
  scene.push(&cube4);

  // scene.push(&sphere3);

  PontualLS ls1 { Vector(-100, 140, -20), Vector(0.7, 0.7, 0.7) };

  scene.pushLightSource(&ls1);

  for (int x = 0; x < WIDTH_CANVAS; x+=1) {
    for (int y = 0; y < HEIGHT_CANVAS; y+=1) {
      Vector coord = canvas.toWindow(Vector(x, y));
      Vector origin = scene.getRay().getCamera();

      Color color = scene.paint(origin, coord);
      int pos = x + (HEIGHT_CANVAS * y);

      pixels[pos] = color;
    }
  }

  sdlEngine.atualizarCanvas((int *) pixels);

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        quit = true;
    }

    // sdlEngine.atualizarCanvas((int *)pixels);
    sdlEngine.atualizarJanela();
  }

  return 0;
}
