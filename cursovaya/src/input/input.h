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
      int maxLength;

    public:
      Input();

      std::string getCurrentValue();

      void setCurrentValue(std::string);

      void setMaxLength(int);

      void clear();

      void handleEvent(SDL_Event);

      void render(SDL_Renderer*, int, int);
  };

#endif
