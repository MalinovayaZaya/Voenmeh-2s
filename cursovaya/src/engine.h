#include <iostream>
#include <string>

#include "../lib/sdl2/include/SDL.h"
#include "../lib/sdl2_ttf/include/SDL_ttf.h"

#ifndef _ENGINE
#define _ENGINE

namespace ENGINE {
  void init();

  void destroy();

  SDL_Window *createWindow(std::string title, int *outWidth, int *outHeight);

  SDL_Renderer *createRenderer(SDL_Window *window);

  bool shouldLoop(SDL_Event *event, bool* quit);

  void beforeRender(SDL_Renderer *renderer);

  void afterRender(SDL_Renderer *renderer);

  void renderText(SDL_Renderer *renderer, int x, int y, std::string text, const unsigned int fontSize = 16);
}

#endif
