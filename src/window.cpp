#include "cGAY/window.h"

void Window::eventHandler() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      exit(0);
      break;
    }
  }
}

Window::Window(const char *title, const uint width, const uint height) {
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                            SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (!window) {
    printf("Failed to open window: %s\n", SDL_GetError());
    exit(1);
  }
}

Window::~Window() {
  SDL_DestroyWindow(window);
}
