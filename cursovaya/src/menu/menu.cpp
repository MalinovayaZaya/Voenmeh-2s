#include "menu.h"

Menu::Menu(int optionsCount, const char **rawOptions)
{
  for (int i = 0; i < optionsCount; i++)
  {
    options.insert(std::pair<int, const char *>(i, rawOptions[i]));
  }
}

const char **Menu::getOptions(int *outCount)
{
  const char** rawOptions = new const char*[options.size()];
  
  int index = 0;
  for (std::map<int, const char*>::iterator iterator = options.begin(); iterator != options.end(); iterator++, index++)
  {
    rawOptions[index] = (*iterator).second;
  }
  *outCount = index;

  return rawOptions;
}

const char *Menu::getOption(int key)
{
  std::map<int, const char*>::iterator iterator = options.find(key);

  if (iterator != options.end()) {
    return (*iterator).second;
  }

  return NULL;
}
