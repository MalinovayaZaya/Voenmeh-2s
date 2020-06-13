#include <iostream>
#include <string>

#include "./lib/sdl2/include/SDL.h"
#include "./lib/sdl2_ttf/include/SDL_ttf.h"

#include "src/utils/utils.h"
#include "src/engine.h"
#include "src/menu/menu.h"
#include "src/input/input.h"
#include "src/core/linkedList/linked_list.cpp"
#include "src/core/train/train.h"
#include "src/core/trainOrm/train_orm.h"

#include "src/screens/screen_config.cpp"
#include "src/screens/mainMenu/main_menu.h"
#include "src/screens/addTrain/add_train_screen.h"

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
  TrainORM trainOrm;

  ENGINE::init();

  window = ENGINE::createWindow("Trains. Author: P. Malinina", &width, &height);
  HELPERS::escapeNullptr(window, "Window creation");

  renderer = ENGINE::createRenderer(window);
  HELPERS::escapeNullptr(renderer, "Renderer creation");

  // Screens
  MainMenuScreen mainMenuScreen;
  AddTrainScreen addTrainScreen(trainOrm);

  while (ENGINE::shouldLoop(&event, &quit))
  {
    ENGINE::beforeRender(renderer);

    // Render App Title
    ENGINE::renderText(renderer, 12, 12, "Trains. Author: P. Malinina", 32);

    switch (screen)
    {
    case Screen::MAIN_MENU:
      mainMenuScreen.render(renderer, event, quit, screen);
      break;

    case Screen::ADD_TRAIN:
      addTrainScreen.render(renderer, event, quit, screen);

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
