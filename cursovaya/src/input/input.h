#include <string>

#include "../../lib/sdl2/include/SDL.h"
#include "../engine.h"

#ifndef _INPUT
#define _INPUT

class Input
  {
    private:
      Uint32 prevTextEventTimestamp;
      Uint32 prevKeydownEventTimestamp;
      std::string value;

    public:
      Input();

      std::string getCurrentValue();

      void resetInput();

      void handleEvent(SDL_Event event);

      void render(SDL_Renderer *renderer, int x, int y);
  };

#endif
