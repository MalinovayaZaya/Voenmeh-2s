#include "trains_screen.h"
#include "../screen_config.cpp"
#include "../../engine.h"

TrainsScreen::TrainsScreen(TrainORM *orm)
{
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
    const SDL_Keycode keycode = event.key.keysym.sym;

    if (keycode == SDLK_ESCAPE)
    {
      screen = Screen::MAIN_MENU;
    }
  }
}
