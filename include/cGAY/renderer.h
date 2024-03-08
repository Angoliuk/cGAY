#pragma once
#include "indecludes.h"
#include "window.h"

class Renderer {
  friend class Resources;

private:
public:
  SDL_Renderer *renderer;

  void drawTexture(SDL_Texture *texture, const int x, const int y);

  void clear();

  void update();

  Renderer(Window *window);

  ~Renderer();
};
