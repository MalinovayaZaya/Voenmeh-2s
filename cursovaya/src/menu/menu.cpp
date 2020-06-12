#include "menu.h"

Menu::Menu() {};

Menu::Menu(int optionsCount, std::string rawOptions[])
{
  for (int i = 0; i < optionsCount; i++)
  {
    options.insert(std::pair<int, std::string>(i, rawOptions[i]));
  }
}

std::string* Menu::getOptions(int *outCount)
{
  std::string* rawOptions = new std::string[options.size()];
  
  int index = 0;
  for (std::map<int, std::string>::iterator iterator = options.begin(); iterator != options.end(); iterator++, index++)
  {
    rawOptions[index] = (*iterator).second;
  }
  *outCount = index;

  return rawOptions;
}

std::string Menu::getOption(int key)
{
  std::map<int, std::string>::iterator iterator = options.find(key);

  if (iterator != options.end()) {
    return (*iterator).second;
  }

  return NULL;
}

void Menu::render(SDL_Renderer *renderer, int x, int y)
{
  int optionsCount = 0;
  std::string* options = getOptions(&optionsCount);

  for (int i = 0; i < optionsCount; i++)
  {
    ENGINE::renderText(renderer, x, y + 20 * i, options[i]);
  }
}