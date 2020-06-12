#include <iostream>

#include "utils.h"

int HELPERS::escapeNegativeResult(const int result, const char action[])
{
  if (result != 0)
  {
    std::cout << "SDL Error: " << action << " : " << SDL_GetError() << std::endl;

    exit(result);
  }

  return result;
}

void HELPERS::escapeNullptr(void *pointer, const char action[])
{
  if (pointer == nullptr)
  {
    std::cout << "SDL Error: " << action << " : " << SDL_GetError() << std::endl;

    exit(1);
  }
}

int HELPERS::getCStyleStringLength(const char *string)
{
  int stringLength = 0;
  const char *iterator = string;

  while (*iterator != '\0')
  {
    iterator++;
    stringLength++;
  }

  return stringLength;
}

void TEXT_RENDER::blitTextToSurface(
    SDL_Surface *surface,
    SDL_Rect *rect,
    const char *text,
    unsigned short fontSize,
    SDL_Color color)
{
  TTF_Font *font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", fontSize);
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);

  SDL_BlitSurface(textSurface, NULL, surface, rect);

  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}
