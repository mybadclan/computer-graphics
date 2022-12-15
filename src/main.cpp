
#include <iostream>

#include "./engine/SDLEngine.h"
#include "engine/Window.hpp"
#include "engine/Canvas.hpp"
#include "engine/Scene.hpp"

#include "math/Vector.hpp"
#include "math/Matrix.hpp"

#include "lightSource/PontualLS.hpp"
#include "lightSource/DirectionalLS.hpp"
#include "lightSource/AmbientLS.hpp"
#include "lightSource/SpotLS.hpp"

#include "utils/Model.hpp"
#include "utils/Color.hpp"
#include "utils/ShapeConfig.hpp"

#include "shapes/Shape.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"
#include "shapes/Cube.hpp"
#include "shapes/Cylinder.hpp"
#include "shapes/Cone.hpp"
#include "shapes/Recipient.hpp"
#include "shapes/Ray.hpp"

#include "image.hpp"

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

  Window window { 200, 200, -30 };
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

  Sphere sphere1 { Vector(0, 30, -30), 10, m1 };

  Plane plane1 { Vector(0, -50, 0), Vector(0, 1, 0), m2 };

  ShapeConfig sc1 { Vector(0, -40, -50), Vector(0, 1, 0), 5, 20 };
  Cylinder cylinder1 { sc1, m1 };
  Cone cone1 { sc1, m2 };

  Cube cube1 { m1 };
  Cube cube2 { m1 };
  Cube cube3 { m1 };
  Cube cube4 { m1 };
  Cube cube5 { m1 };

  ShapeConfig sc2 { Vector(0, -50, -90), Vector(0, 1, 0), 50, 50 };
  Recipient recipient1 { sc2, m1 };

  // Matrix auxM1 = Matrix::translate(-10, -50, -40) * Matrix::scale(5, 20, 5);
  // Matrix auxM2 = Matrix::translate(10, -50, -40) * Matrix::scale(5, 20, 5);
  // Matrix auxM3 = Matrix::translate(-10, -50, -60) * Matrix::scale(5, 20, 5);
  // Matrix auxM4 = Matrix::translate(10, -50, -60) * Matrix::scale(5, 20, 5);
  // Matrix auxM5 = Matrix::translate(-6, -20, -20) * Matrix::scale(15, 2, 15);


  // cube1.transform(auxM1, SCALE);
  // cube2.transform(auxM2, SCALE);
  // cube3.transform(auxM3, SCALE);
  // cube4.transform(auxM4, SCALE);
  // cube5.transform(auxM5, SCALE);

  // recipient1.pushShape(&cube1);
  // recipient1.pushShape(&cube2);
  // recipient1.pushShape(&cube3);
  // recipient1.pushShape(&cube4);
  // recipient1.pushShape(&cube5);

  scene.push(&sphere1);
  scene.push(&cylinder1);
  scene.push(&plane1);
  // scene.push(&cube1);
  // scene.push(&cube2);
  // scene.push(&cube3);
  // scene.push(&cube4);
  // scene.push(&recipient1);

  Vector direction =  Vector(0, 135, 300).normalized();

  PontualLS ls1 { Vector(100, 140, -20), Vector(0.7, 0.7, 0.7) };
  DirectionalLS ls2 { direction.normalized(), Vector(0.7, 0.7, 0.7) };
  AmbientLS ls3 { Vector(0.4, 0.4, 0.4) };

  SpotLS ls4 { Vector(0, 30, -80), Vector(0, -1, 0), Vector(0.6, 0.6, 0.4), 30.0 };

  scene.setPontualLS(&ls1);
  scene.setDirectionalLS(&ls2);
  scene.setAmbientLS(&ls3);
  scene.setSpotLS(&ls4);

  scene.togglePontual();
  scene.toggleAmbient();

  createImage(&scene, &canvas, pixels, WIDTH_CANVAS, HEIGHT_CANVAS);

  sdlEngine.atualizarCanvas((int *) pixels);

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) {
        quit = true;
      }

      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o) {
        scene.toggleOrthogonalVision();
        createImage(&scene, &canvas, pixels, WIDTH_CANVAS, HEIGHT_CANVAS);

        sdlEngine.atualizarCanvas((int *)pixels);
      }

      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_j) {
        scene.togglePontual();
        createImage(&scene, &canvas, pixels, WIDTH_CANVAS, HEIGHT_CANVAS);

        sdlEngine.atualizarCanvas((int *)pixels);
      }

      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k) {
        scene.toggleDirectional();
        createImage(&scene, &canvas, pixels, WIDTH_CANVAS, HEIGHT_CANVAS);

        sdlEngine.atualizarCanvas((int *)pixels);
      }

      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l) {
        scene.toggleSpot();
        createImage(&scene, &canvas, pixels, WIDTH_CANVAS, HEIGHT_CANVAS);

        sdlEngine.atualizarCanvas((int *)pixels);
      }
    }

    // sdlEngine.atualizarCanvas((int *)pixels);
    sdlEngine.atualizarJanela();
  }

  return 0;
}
