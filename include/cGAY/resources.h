#pragma once
#include "indecludes.h"
#include "renderer.h"

class Resources {
private:
  std::map<const char *, SDL_Texture *> textures;
  Renderer *renderer;

public:
  SDL_Texture *getTextureByPath(const char *path);

  void loadTexture(const char *path);

  Resources(Renderer *renderer);

  ~Resources();
};
