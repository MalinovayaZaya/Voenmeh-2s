#include "../../../lib/sdl2/include/SDL.h"

#include "../../core/train/train.h"
#include "../../core/trainOrm/train_orm.h"
#include "../../trainList/train_list.h"

#ifndef _TRAINS_SCREEN
#define _TRAINS_SCREEN

class TrainsScreen
{
private:
  Uint32 prevKeyEventTimestamp;
  TrainORM* trainOrm;
  TrainList trainList;

public:
  TrainsScreen(TrainORM *);

  void render(SDL_Renderer *, SDL_Event, bool &, int &);
};

#endif
