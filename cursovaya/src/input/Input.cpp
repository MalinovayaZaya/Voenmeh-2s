#include "input.h"

Input::Input()
{
  resetInput();
}

std::string Input::getCurrentValue()
{
  return value;
}

void Input::resetInput()
{
  value = "";
  prevTextEventTimestamp = 0;
  prevKeydownEventTimestamp = 0;
}

void Input::handleEvent(SDL_Event event)
{
  switch (event.type)
  {
  case SDL_TEXTINPUT:
  {
    const Uint32 eventTimestamp = event.text.timestamp;

    if (eventTimestamp != prevTextEventTimestamp)
    {
      prevTextEventTimestamp = eventTimestamp;

      value += event.text.text;
    }
  }
  break;

  case SDL_KEYDOWN:
  {
    const Uint32 eventTimestamp = event.key.timestamp;
    const SDL_Keycode keycode = event.key.keysym.sym;

    if (eventTimestamp != prevKeydownEventTimestamp)
    {
      switch (keycode)
      {
      case SDLK_BACKSPACE:
        if (value.size())
        {
          value.pop_back();
        }
        break;
      }
    }
  }
  break;
  }
}

void Input::render(SDL_Renderer *renderer, int x, int y)
{
  ENGINE::renderText(renderer, x, y, value, 16);
}
