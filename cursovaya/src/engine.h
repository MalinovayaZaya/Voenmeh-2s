#include <iostream>

#include "../lib/sdl2/include/SDL.h"
#include "../lib/sdl2_ttf/include/SDL_ttf.h"

#ifndef _ENGINE
#define _ENGINE

namespace ENGINE {
  void init();

  void destroy();

  SDL_Window *createWindow(const char title[], int *outWidth, int *outHeight);

  SDL_Renderer *createRenderer(SDL_Window *window);

  void renderText(const char *text, SDL_Renderer *renderer, int x, int y);

  bool shouldLoop(SDL_Event *event, bool* quit);

  void beforeRender(SDL_Renderer *renderer);

  void afterRender(SDL_Renderer *renderer);
}

#endif
