#include <map>
#include <string>

#include "../engine.h"

#ifndef _MENU
#define _MENU

class Menu
{
  private:
    std::map<int, std::string> options;

  public:
    Menu();

    Menu(int optionsCount, std::string rawOptions[]);

    std::string* getOptions(int *outCount);

    std::string getOption(int key);

    void render(SDL_Renderer *renderer, int x, int y);
};

#endif
