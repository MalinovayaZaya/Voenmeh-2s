#include <iostream>

#include "utils.h"

int HELPERS::escapeNegativeResult(const int result, std::string action)
{
  if (result != 0)
  {
    std::cout << "SDL Error: " << action << " : " << SDL_GetError() << std::endl;

    exit(result);
  }

  return result;
}

void HELPERS::escapeNullptr(void *pointer, std::string action)
{
  if (pointer == nullptr)
  {
    std::cout << "SDL Error: " << action << " : " << SDL_GetError() << std::endl;

    exit(1);
  }
}

void HELPERS::blitTextToSurface(
    SDL_Surface *surface,
    SDL_Rect *rect,
    std::string text,
    unsigned short fontSize,
    SDL_Color color)
{
  TTF_Font *font = TTF_OpenFont("fonts/Roboto-Medium.ttf", fontSize);
  SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

  SDL_BlitSurface(textSurface, NULL, surface, rect);

  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}
