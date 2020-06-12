#include <iostream>
#include <string>

#include "./lib/sdl2/include/SDL.h"
#include "./lib/sdl2_ttf/include/SDL_ttf.h"
#include "src/utils/utils.h"
#include "src/engine.h"
#include "src/menu/menu.h"

namespace Screen
{
  const int MAIN_MENU = 0;
  const int LOAD_DB = 1;
}; // namespace Screen

// --- Screen classes declaration
class MainMenuScreen
{
private:
  Menu menu;

public:
  MainMenuScreen();

  void render(SDL_Renderer *renderer, SDL_Event event, int &screen);
};

// --- App entry point
int main(int argc, char *argv[])
{
  int width;
  int height;
  SDL_DisplayMode displayMode;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit = false;
  int screen = Screen::MAIN_MENU;

  ENGINE::init();

  window = ENGINE::createWindow("Trains. Author: P. Malinina", &width, &height);
  HELPERS::escapeNullptr(window, "Window creation");

  renderer = ENGINE::createRenderer(window);
  HELPERS::escapeNullptr(renderer, "Renderer creation");

  // Screens
  MainMenuScreen mainMenuScreen;

  while (ENGINE::shouldLoop(&event, &quit))
  {
    ENGINE::beforeRender(renderer);

    // Render App Title
    ENGINE::renderText(renderer, 12, 12, "Trains. Author: P. Malinina", 32);

    switch (screen)
    {
    case Screen::MAIN_MENU:
      mainMenuScreen.render(renderer, event, screen);
      break;

    default:
      break;
    }

    ENGINE::afterRender(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  ENGINE::destroy();
  return 0;
}

// --- Screen classess implementation

// MainMenuScreen
MainMenuScreen::MainMenuScreen()
{
  std::string options[] = {
      "1. Load trainsDB",
      "2. Print trainsDB",
      "3. Find train",
      "4. Add train",
      "5. Remove train",
      "6 or ESCAPE. Exit Program"};

  menu = Menu(5, options);
}

void MainMenuScreen::render(SDL_Renderer *renderer, SDL_Event event, int &screen)
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
      screen = Screen::LOAD_DB;
      break;
    }
  }
}
