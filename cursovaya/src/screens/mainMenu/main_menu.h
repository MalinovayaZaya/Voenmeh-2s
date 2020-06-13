#ifndef _MAIN_MENU
#define _MAIN_MENU

#include "../../../lib/sdl2/include/SDL.h"
#include "../../menu/menu.h"

class MainMenuScreen
{
private:
  Menu menu;

public:
  MainMenuScreen();

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
};

#endif
