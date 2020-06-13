#include "add_train_screen.h"
#include "../screen_config.cpp"

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
