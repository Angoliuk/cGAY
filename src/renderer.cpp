#include "cGAY/renderer.h"

void Renderer::drawTexture(SDL_Texture *texture, const int x, const int y) {
  SDL_Rect rect{x, y, 500, 500};

  SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
  // std::cout << rect.w << " " << rect.h << " :dest rest\n";
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::update() {
  SDL_RenderPresent(renderer);
}

Renderer::Renderer(Window *window) {
  renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    printf("Failed renderer: %s\n", SDL_GetError());
    exit(1);
  }
};

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
}
