#include "cGAY/resources.h"

SDL_Texture *Resources::getTextureByPath(const char *path) {
  auto texture = textures.find(path);

  if (texture == textures.end()) {
    printf("Failed getTextureByPath: %s\n", SDL_GetError());
    exit(1);
  }

  return texture->second;
}

void Resources::loadTexture(const char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);

  if (!surface) {
    printf("Failed surface: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->renderer, surface);

  if (!texture) {
    printf("Failed texture: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_FreeSurface(surface);

  textures.insert(std::make_pair(path, texture));
}

Resources::Resources(Renderer *renderer) : renderer(renderer) {
}

Resources::~Resources() {
  std::for_each(textures.begin(), textures.end(), [](auto pair) { SDL_DestroyTexture(pair.second); });
}
