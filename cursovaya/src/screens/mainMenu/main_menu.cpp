#include "main_menu.h"
#include "../screen_config.cpp"

MainMenuScreen::MainMenuScreen()
{
  std::string options[] = {
      "1. Load trainsDB",
      "2. Print trainsDB",
      "3. Add train",
      "4. Query trains by destination and time interval",
      "5. Remove train",
      "6 or ESCAPE. Exit Program"};

  menu = Menu(6, options);
}

void MainMenuScreen::render(SDL_Renderer *renderer, SDL_Event event, bool &quit, int &screen)
{
  const int xOffset = 12;

  ENGINE::renderText(renderer, xOffset, 64, "Choose action:", 22);
  menu.render(renderer, xOffset, 100);

  if (event.type == SDL_KEYDOWN)
  {
    SDL_Keycode keycode = event.key.keysym.sym;

    switch (keycode)
    {
    case SDLK_3:
      screen = Screen::ADD_TRAIN;
      SDL_WaitEvent(&event);
      break;

    case SDLK_6:
    case SDLK_ESCAPE:
      quit = true;
      break;
    }
  }
}