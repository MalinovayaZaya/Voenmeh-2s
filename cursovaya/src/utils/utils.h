#include "../../lib/sdl2/include/SDL.h"
#include "../../lib/sdl2_ttf/include/SDL_ttf.h"

#ifndef _UTILS
#define _UTILS

namespace HELPERS {
  int escapeNegativeResult(const int result,  const char action[]);

  void escapeNullptr(void* pointer, const char action[]);

  int getCStyleStringLength(const char* string);
}

namespace TEXT_RENDER {
  void blitTextToSurface(SDL_Surface* surface, SDL_Rect* rect, const char text[], unsigned short fontSize, SDL_Color color);
}

#endif
