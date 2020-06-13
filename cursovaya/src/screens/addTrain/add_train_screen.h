#include <string>

#include "../../input/input.h"
#include "../../core/train/train.h"
#include "../../core/trainOrm/train_orm.h"

#ifndef _ADD_TRAIN_SCREEN
#define _ADD_TRAIN_SCREEN

class AddTrainScreen
{
private:
  TrainORM* trainOrm;
  Train train;
  int inputFieldIndex;
  Input inputs[5];
  bool shouldShowErrorMessage;
  std::string errorMessage;

public:
  AddTrainScreen(TrainORM *);

  void validateInputField(int &);

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
};

#endif
