#include "input.h"

Input::Input()
{
  value = "";
  prevTextEventTimestamp = 0;
  prevKeydownEventTimestamp = 0;

  maxLength = -1;
}

std::string Input::getCurrentValue()
{
  return value;
}

void Input::setCurrentValue(std::string _value)
{
  value = _value;
}

void Input::setMaxLength(int _maxLength)
{
  maxLength = _maxLength;
}

void Input::clear()
{
  value = "";
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

      if (maxLength != -1)
      {
        if (value.size() > maxLength)
        {
          value = value.substr(0, maxLength);
        }
      }
    }
  }
  break;

  case SDL_KEYDOWN:
  {
    const Uint32 eventTimestamp = event.key.timestamp;
    const SDL_Keycode keycode = event.key.keysym.sym;

    if (eventTimestamp != prevKeydownEventTimestamp)
    {
      prevKeydownEventTimestamp = eventTimestamp;
      
      switch (keycode)
      {
      case SDLK_BACKSPACE:
        if (value.size())
        {
          value.pop_back();
        }
        else
        {
          value = "";
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
  if (value.size())
  {
    ENGINE::renderText(renderer, x, y, value, 16);
  }
}
