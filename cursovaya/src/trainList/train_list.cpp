#include <string>

#include "train_list.h"
#include "../screens/screen_config.cpp"
#include "../engine.h"

void TrainList::setList(LinkedList<Train> *list)
{
  trainList = list;
  page = 0;
}

void TrainList::render(SDL_Renderer* renderer, int x, int y)
{
  if ((*trainList).getCount() == 0)
  {
    return;
  }
  
  Item<Train>* iterator = (*trainList).getBegin();
  int index = 0;

  while (iterator != nullptr)
  {
    Train train = iterator->getData();

    std::string row = "";

    row += std::to_string(train.getIndex()) + " ";
    row += train.getDestination() + " ";
    row += std::to_string(train.getDepartureTimestamp()) + " ";
    row += std::to_string(train.getPathTimeInMs()) + " ";
    row += std::to_string(train.getHasTickets());

    ENGINE::renderText(renderer, x, y + index * 20, row, 16);

    iterator = iterator->getNext();
    index += 1;
  }
}
