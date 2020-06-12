#include <string>

#include "../../lib/sdl2/include/SDL.h"
#include "../../lib/sdl2_ttf/include/SDL_ttf.h"

#ifndef _UTILS
#define _UTILS

namespace HELPERS {
  int escapeNegativeResult(const int result, std::string action);

  void escapeNullptr(void* pointer, std::string action);

  void blitTextToSurface(SDL_Surface* surface, SDL_Rect* rect, std::string text, unsigned short fontSize, SDL_Color color);
}

#endif
