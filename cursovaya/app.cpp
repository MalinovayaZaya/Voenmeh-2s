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

namespace Screen
{
  const int MAIN_MENU = 0;
  const int ADD_TRAIN = 1;
}; // namespace Screen

// --- Screen classes declaration

// MainMenuScreen
class MainMenuScreen
{
private:
  Menu menu;

public:
  MainMenuScreen();

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
};

// AddTrainScreen
class AddTrainScreen
{
private:
  TrainORM trainOrm;
  Train train;
  int inputFieldIndex;
  Input inputs[5];
  bool shouldShowErrorMessage;
  std::string errorMessage;

public:
  AddTrainScreen(TrainORM &);

  void validateInputField(int &);

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
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

// --- Screen classess implementation

// MainMenuScreen
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

// AddTrainScreen
AddTrainScreen::AddTrainScreen(TrainORM &_trainOrm)
{
  trainOrm = _trainOrm;
  inputFieldIndex = 0;

  inputs[0].setMaxLength(9);
  inputs[1].setMaxLength(4);
  inputs[2].setMaxLength(9);
  inputs[3].setMaxLength(9);
  inputs[4].setMaxLength(1);
}

void AddTrainScreen::validateInputField(int &inputFieldIndex)
{
  switch (inputFieldIndex)
  {
  case 0:
  {
    int trainIndex;

    try
    {
      trainIndex = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      train.setIndex(trainIndex);
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given train index is not number. Please, try again.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;

  case 1:
  {
    std::string destination = inputs[inputFieldIndex].getCurrentValue();

    if (destination == "")
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given train destination is empty. Please, specify destination.";
    }
    else
    {
      train.setDestination(destination);
      inputFieldIndex += 1;
    }
  }
  break;

  case 2:
  {
    int departureTimestamp;

    try
    {
      departureTimestamp = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      train.setDepartureTimestamp(departureTimestamp);
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given train timestamp is not number. Please, try again.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;

  case 3:
  {
    int pathTime;

    try
    {
      pathTime = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      train.setPathTimeInMs(pathTime);
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given train path time is not number. Please, try again.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;

  case 4:
  {
    bool hasTickets;

    try
    {
      hasTickets = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      train.setHasTickets(hasTickets == 1);
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "You should enter 1, if train has tickets to sell, and 0 if not.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;
  }
}

void AddTrainScreen::render(SDL_Renderer *renderer, SDL_Event event, bool &quit, int &state)
{
  const bool inputFiledIndexInBounds = inputFieldIndex < 5;
  const int xOffset = 12;
  const int yFieldOffset = 64;
  const int fieldTitleFontSize = 22;
  std::string fieldTitle;

  switch (inputFieldIndex)
  {
  case 0:
    fieldTitle = "Enter train index:";
    break;

  case 1:
    fieldTitle = "Enter train destination (max 4 symbols):";
    break;

  case 2:
    fieldTitle = "Enter train departure timestamp:";
    break;

  case 3:
    fieldTitle = "Enter train path time in ms:";
    break;

  case 4:
    fieldTitle = "Has train tickets to sell? (Enter 1, if has, and 0, if not)";
    break;

  case 5:
    state = Screen::MAIN_MENU;
    break;
  }

  if (inputFiledIndexInBounds)
  {
    ENGINE::renderText(renderer, xOffset, yFieldOffset, fieldTitle, fieldTitleFontSize);
    inputs[inputFieldIndex].handleEvent(event);
    inputs[inputFieldIndex].render(renderer, xOffset, yFieldOffset + 28);

    // Handle enter
    if (event.type == SDL_KEYDOWN)
    {
      const SDL_Keycode keycode = event.key.keysym.sym;

      if (keycode == SDLK_RETURN)
      {
        validateInputField(inputFieldIndex);
      }
    }

    // Show error message
    if (shouldShowErrorMessage && errorMessage.size())
    {
      if (inputs[inputFieldIndex].getCurrentValue().size() == 0)
      {
        ENGINE::renderText(renderer, xOffset, yFieldOffset + 44, errorMessage, 16);
      }
      else
      {
        shouldShowErrorMessage = false;
      }
    }
  }
}
