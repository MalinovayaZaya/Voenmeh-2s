#include <map>

#ifndef _MENU
#define _MENU

class Menu
{
  private:
    std::map<int, const char*> options;

  public:
    Menu(int optionsCount, const char **rawOptions);

    const char** getOptions(int *outCount);

    const char* getOption(int key);
};

#endif
