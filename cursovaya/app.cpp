#include <iostream>
#include <string>

#include "./lib/sdl2/include/SDL.h"
#include "./lib/sdl2_ttf/include/SDL_ttf.h"
#include "src/utils/utils.h"
#include "src/engine.h"
#include "src/menu/menu.h"

Menu getMenu()
{
  const int OPTIONS_COUNT = 2;
  const char **rawOptions = new const char *[OPTIONS_COUNT];

  rawOptions[0] = "1 Option\0";
  rawOptions[1] = "2 Option\0";

  Menu menu(OPTIONS_COUNT, rawOptions);

  return menu;
}

Menu getSubMenu()
{
  const int OPTIONS_COUNT = 2;
  const char **rawOptions = new const char *[OPTIONS_COUNT];

  rawOptions[0] = "1 SubOption\0";
  rawOptions[1] = "2 SubOption\0";

  Menu menu(OPTIONS_COUNT, rawOptions);

  return menu;
}

void displayMenu(int windowHeight, SDL_Renderer *renderer)
{
  Menu menu = getMenu();
  Menu subMenus[] = {getSubMenu(), getSubMenu()};
  int selectedMenu = -1;
  int selectedOption = -1;
  SDL_Event event;
  bool quit;

  while (ENGINE::shouldLoop(&event, &quit))
  {
    ENGINE::beforeRender(renderer);

    int optionsCount = 0;
    const char **options;

    if (selectedMenu == -1)
    {
      options = menu.getOptions(&optionsCount);
    }
    else if (selectedOption == -1)
    {
      options = subMenus[selectedMenu].getOptions(&optionsCount);
    }

    for (int i = 0; i < optionsCount; i++)
    {
      ENGINE::renderText(options[i], renderer, 0, i * 20);
    }

    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_1:
        if (selectedMenu == -1)
        {
          selectedMenu = 0;
        }
        else if (selectedOption == -1)
        {
          selectedOption = 0;
        }
        break;

      case SDLK_2:
        if (selectedMenu == -1)
        {
          selectedMenu = 1;
        }
        else if (selectedOption == -1)
        {
          selectedOption = 1;
        }
        break;
      }
    }

    if (selectedMenu != -1)
    {
      ENGINE::renderText(menu.getOption(selectedMenu), renderer, 0, windowHeight - 50);
    }

    if (selectedOption != -1)
    {
      ENGINE::renderText(subMenus[selectedMenu].getOption(selectedOption), renderer, 20, windowHeight - 30);
    }

    ENGINE::afterRender(renderer);
    SDL_PumpEvents();
  }
}

void handleInput(SDL_Renderer *renderer)
{
  SDL_StartTextInput();

  Uint32 prevEventTimestamp = -1;
  std::string input;
  SDL_Event event;
  bool quit;

  while (ENGINE::shouldLoop(&event, &quit))
  {
    ENGINE::beforeRender(renderer);
    switch (event.type)
    {
    case SDL_TEXTINPUT:
      if (prevEventTimestamp != event.text.timestamp)
      {
        input += event.text.text;

        prevEventTimestamp = event.text.timestamp;
      }
      break;

    case SDL_KEYDOWN:
      if (prevEventTimestamp != event.key.timestamp)
      {
        if (event.key.keysym.sym == SDLK_BACKSPACE && input.size())
        {
          input.pop_back();
        }

        prevEventTimestamp = event.key.timestamp;
      }
      break;
    }

    ENGINE::renderText(input.c_str(), renderer, 0, 0);
    ENGINE::afterRender(renderer);
    SDL_PumpEvents();
  }

  SDL_StopTextInput();
}

int main(int argc, char *argv[])
{
  int width;
  int height;
  SDL_DisplayMode displayMode;
  SDL_Window *window;
  SDL_Renderer *renderer;

  ENGINE::init();

  window = ENGINE::createWindow("Hello, world!", &width, &height);
  HELPERS::escapeNullptr(window, "Window creation");

  renderer = ENGINE::createRenderer(window);
  HELPERS::escapeNullptr(renderer, "Renderer creation");

  displayMenu(height, renderer);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  ENGINE::destroy();
  return 0;
}
