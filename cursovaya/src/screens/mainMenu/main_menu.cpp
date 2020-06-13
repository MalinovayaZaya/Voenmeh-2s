#include "main_menu.h"
#include "../screen_config.cpp"

MainMenuScreen::MainMenuScreen()
{
  std::string options[] = {
      "1. Print trainsDB",
      "2. Add train",
      "3. Query trains by destination and time interval",
      "4. Exit program"};

  menu = Menu(4, options);
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
    case SDLK_1:
      screen = Screen::PRINT_TRAINS;
      SDL_WaitEvent(&event);
      break;

    case SDLK_2:
      screen = Screen::ADD_TRAIN;
      SDL_WaitEvent(&event);
      break;
      
    case SDLK_3:
      screen = Screen::QUERY_TRAINS;
      SDL_WaitEvent(&event);
      break;

    case SDLK_4:
      quit = true;
      break;
    }
  }
}