#include "engine/Scene.hpp"
#include "engine/Canvas.hpp"
#include "utils/Color.hpp"

void createImage(Scene* scene, Canvas* canvas, Color* pixels, int WIDTH, int HEIGHT) {
  for (int x = 0; x < WIDTH; x+=1) {
    for (int y = 0; y < HEIGHT; y+=1) {
      Vector coord = canvas->toWindow(Vector(x, y));
      Vector origin = scene->getRay().getCamera();

      Color color = scene->paint(origin, coord);
      int pos = x + (HEIGHT * y);

      pixels[pos] = color;
    }
  }
}