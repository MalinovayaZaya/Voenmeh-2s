#include "query_screen.h"
#include "../screen_config.cpp"
#include "../../engine.h"

QueryScreen::QueryScreen(TrainORM *orm)
{
  prevKeyEventTimestamp = 0;

  trainOrm = orm;
  trainList = nullptr;

  inputFieldIndex = 0;

  inputs[0].setMaxLength(3);
  inputs[1].setMaxLength(9);
  inputs[2].setMaxLength(9);
}

void QueryScreen::validateInputField(int &inputFieldIndex)
{
  switch (inputFieldIndex)
  {
  case 0:
  {
    std::string destination = inputs[inputFieldIndex].getCurrentValue();

    if (destination == "")
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given train destination is empty. Please, specify destination.";
    }
    else
    {
      dest = destination;
      inputFieldIndex += 1;
    }
  }
  break;

  case 1:
  {
    int _fromInterval;

    try
    {
      _fromInterval = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      fromInterval = _fromInterval;
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given interval is not number. Please, try again.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;

  case 2:
  {
    int _toInterval;

    try
    {
      _toInterval = std::stoi(inputs[inputFieldIndex].getCurrentValue());

      toInterval = _toInterval;
      inputFieldIndex += 1;
    }
    catch (std::invalid_argument e)
    {
      shouldShowErrorMessage = true;
      errorMessage = "Given interval time is not number. Please, try again.";
      inputs[inputFieldIndex].clear();
    }
  }
  break;
  }
}

void QueryScreen::render(SDL_Renderer *renderer, SDL_Event event, bool &quit, int &screen)
{
  const bool inputFiledIndexInBounds = inputFieldIndex < 3;
  const int xOffset = 12;
  const int yFieldOffset = 64;
  const int fieldTitleFontSize = 22;
  std::string fieldTitle;

  switch (inputFieldIndex)
  {
  case 0:
    fieldTitle = "Enter train destination (max 3 symbold):";
    break;

  case 1:
    fieldTitle = "Enter 'fromInterval' as timestamp:";
    break;

  case 2:
    fieldTitle = "Enter 'toInterval' as timestamp:";
    break;

  case 3:
    if (trainList == nullptr)
    {
      trainList = new TrainList();
      trainList->setList(trainOrm->queryTrainsByDestinationAndTimeInterval(dest, fromInterval, toInterval));
    }
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

      if (keycode == SDLK_ESCAPE)
      {
        screen = Screen::MAIN_MENU;
        SDL_WaitEvent(&event);
        reset();
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
  else
  {
    ENGINE::renderText(renderer, xOffset, yFieldOffset, "Filtered trains:", 24);
    trainList->render(renderer, xOffset, yFieldOffset + 28);

    // Handle quit
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.timestamp != prevKeyEventTimestamp)
      {
        const SDL_Keycode keycode = event.key.keysym.sym;

        prevKeyEventTimestamp = event.key.timestamp;

        switch (keycode)
        {
        case SDLK_RIGHT:
          trainList->nextPage();
          break;

        case SDLK_LEFT:
          trainList->prevPage();
          break;

        case SDLK_ESCAPE:
          screen = Screen::MAIN_MENU;
          SDL_WaitEvent(&event);
          reset();
          break;
        }
      }
    }
  }
}

void QueryScreen::reset()
{
  inputFieldIndex = 0;

  for (int i = 0; i < 3; i++)
  {
    inputs[i].clear();
  }

  dest = "";
  fromInterval = -1;
  toInterval = -1;

  delete trainList;
  trainList = nullptr;
}
