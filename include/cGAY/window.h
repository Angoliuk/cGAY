#pragma once
#include "indecludes.h"

class Window {
  friend class Renderer;

private:
  SDL_Window *window;

public:
  void eventHandler();

  Window(const char *title, const uint width, const uint height);

  ~Window();
};
