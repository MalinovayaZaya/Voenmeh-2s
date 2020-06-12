#include "engine.h"
#include "./utils/utils.h"

void ENGINE::init()
{
  HELPERS::escapeNegativeResult(SDL_Init(SDL_INIT_EVERYTHING), "SDL Init");
  HELPERS::escapeNegativeResult(TTF_Init(), "TTF Init");
}

void ENGINE::destroy()
{
  TTF_Quit();
  SDL_Quit();
}

SDL_Window *ENGINE::createWindow(const char title[], int *outWidth, int *outHeight)
{
  SDL_Window *window;
  SDL_DisplayMode displayMode;

  HELPERS::escapeNegativeResult(SDL_GetDesktopDisplayMode(0, &displayMode), "Get DisplayMode");

  *outWidth = displayMode.w / 2;
  *outHeight = displayMode.h / 2;

  window = SDL_CreateWindow(
      title,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      displayMode.w / 2,
      displayMode.h / 2,
      SDL_WINDOW_SHOWN);

  return window;
}

SDL_Renderer *ENGINE::createRenderer(SDL_Window *window)
{
  SDL_Renderer *renderer;

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  return renderer;
}

void ENGINE::renderText(const char *text, SDL_Renderer *renderer, int x, int y)
{
  const unsigned short FONT_SIZE = 16;
  const int textLength = HELPERS::getCStyleStringLength(text);
  const int width = textLength * FONT_SIZE;
  const int height = FONT_SIZE * 1.7;

  SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
  SDL_Color color = {0, 0, 0, 255};
  SDL_Rect dstRect;
  dstRect.w = width;
  dstRect.h = height;
  dstRect.x = x;
  dstRect.y = y;

  TEXT_RENDER::blitTextToSurface(surface, NULL, text, FONT_SIZE, color);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopy(renderer, texture, NULL, &dstRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

bool ENGINE::shouldLoop(SDL_Event *event, bool *quit)
{
  SDL_PollEvent(event);

  if ((*event).type == SDL_QUIT)
  {
    return false;
  }

  if (*quit == true)
  {
    return false;
  }

  return true;
}

void ENGINE::beforeRender(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void ENGINE::afterRender(SDL_Renderer *renderer)
{
  SDL_RenderPresent(renderer);
}