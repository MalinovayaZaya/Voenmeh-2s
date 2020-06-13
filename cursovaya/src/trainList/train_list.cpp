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

  const int yOffset = 20;
  int index = 0;

  ENGINE::renderText(renderer, x, y, "ID", 16);
  ENGINE::renderText(renderer, x + 50, y, "DEST", 16);
  ENGINE::renderText(renderer, x + 100, y, "DEP_TIME", 16);
  ENGINE::renderText(renderer, x + 200, y, "PATH_TIME", 16);
  ENGINE::renderText(renderer, x + 300, y, "HAS_TICKETS", 16);

  Item<Train> *iterator = getIteratorFromPage(trainList, page, limit);

  while (iterator != nullptr)
  {
    if (index + 1 > limit)
    {
      break;
    }

    Train train = iterator->getData();

    ENGINE::renderText(renderer, x, y + yOffset + index * 20, std::to_string(train.getIndex()), 16);
    ENGINE::renderText(renderer, x + 50, y + yOffset + index * 20, train.getDestination(), 16);
    ENGINE::renderText(renderer, x + 100, y + yOffset + index * 20, std::to_string(train.getDepartureTimestamp()), 16);
    ENGINE::renderText(renderer, x + 200, y + yOffset + index * 20, std::to_string(train.getPathTimeInMs()), 16);
    ENGINE::renderText(renderer, x + 300, y + yOffset + index * 20, std::to_string(train.getHasTickets()), 16);

    iterator = iterator->getNext();
    index += 1;
  }

  // Render pagination info
  ENGINE::renderText(renderer, x, y + 100, "Pages count: " + std::to_string(getPagesCount()), 14);
  ENGINE::renderText(renderer, x, y + 120, "<-", 14);
  ENGINE::renderText(renderer, x + 18, y + 120, std::to_string(page + 1), 14);
  ENGINE::renderText(renderer, x + 32, y + 120, "->", 14);
}
