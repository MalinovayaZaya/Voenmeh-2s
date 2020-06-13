#include "trains_screen.h"
#include "../screen_config.cpp"
#include "../../engine.h"

TrainsScreen::TrainsScreen(TrainORM *orm)
{
  prevKeyEventTimestamp = 0;
  trainOrm = orm;
  trainList.setList(trainOrm->getTrains());
}

void TrainsScreen::render(SDL_Renderer *renderer, SDL_Event event, bool &quit, int &screen)
{
  const int xOffset = 12;
  ENGINE::renderText(renderer, xOffset, 64, "Trains:", 24);
  trainList.render(renderer, xOffset, 100);

  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.timestamp != prevKeyEventTimestamp)
    {
      const SDL_Keycode keycode = event.key.keysym.sym;
      prevKeyEventTimestamp = event.key.timestamp;

      switch (keycode)
      {
      case SDLK_RIGHT:
        trainList.nextPage();
        break;

      case SDLK_LEFT:
        trainList.prevPage();
        break;

      case SDLK_ESCAPE:
        screen = Screen::MAIN_MENU;
        trainList.setPage(0);
        SDL_WaitEvent(&event);
        break;
      }
    }
  }
}
