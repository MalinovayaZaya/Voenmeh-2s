#include <string>

#include "train_list.h"
#include "../screens/screen_config.cpp"
#include "../engine.h"

Item<Train> *getIteratorFromPage(LinkedList<Train> *list, int page, int limit)
{
  Item<Train> *iterator = list->getBegin();
  int count = 0;

  while (iterator != nullptr)
  {
    count += 1;
    int _page = count / limit;

    if (_page == page)
    {
      return iterator;
    }

    iterator = iterator->getNext();
  }

  return nullptr;
}

void TrainList::setList(LinkedList<Train> *list)
{
  trainList = list;
  page = 0;
}

void TrainList::nextPage()
{
  int pagesCount = getPagesCount();

  page += 1;

  if (page + 1 > pagesCount)
  {
    page = pagesCount - 1;
  }
}

void TrainList::prevPage()
{
  page -= 1;

  if (page < 0)
  {
    page = 0;
  }
}

void TrainList::setPage(int _page)
{
  if (page < getPagesCount() && page > -1)
  {
    page = _page;
  }
}

int TrainList::getPagesCount()
{
  int pagesCount = (trainList->getCount() / limit) + (trainList->getCount() % limit != 0 ? 1 : 0);

  return pagesCount;
}

void TrainList::render(SDL_Renderer *renderer, int x, int y)
{
  if (trainList->getCount() == 0)
  {
    return;
  }

  int index = 0;

  Item<Train> *iterator = getIteratorFromPage(trainList, page, limit);

  while (iterator != nullptr)
  {
    if (index + 1 > limit)
    {
      break;
    }

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

  // Render pagination info
  ENGINE::renderText(renderer, x, y + 100, "Pages count: " + std::to_string(getPagesCount()), 14);
  ENGINE::renderText(renderer, x, y + 120, "<-", 14);
  ENGINE::renderText(renderer, x + 18, y + 120, std::to_string(page + 1), 14);
  ENGINE::renderText(renderer, x + 32, y + 120, "->", 14);
}
