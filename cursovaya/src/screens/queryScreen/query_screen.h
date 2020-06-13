#include "../../../lib/sdl2/include/SDL.h"

#include "../../core/trainOrm/train_orm.h"
#include "../../trainList/train_list.h"
#include "../../input/input.h"

#ifndef _QUERY_SCREEN
#define _QUERY_SCREEN

class QueryScreen
{
private:
  std::string dest;
  int fromInterval;
  int toInterval;
  int inputFieldIndex;
  Input inputs[3];
  TrainORM *trainOrm;
  TrainList trainList;
  bool shouldShowErrorMessage;
  std::string errorMessage;

public:
  QueryScreen(TrainORM *);

  void validateInputField(int &);

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
};

#endif
