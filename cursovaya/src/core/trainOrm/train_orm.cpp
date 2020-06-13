#include "train_orm.h"

TrainORM::TrainORM() {}

void TrainORM::addTrain(
    int index,
    std::string destination,
    int depatureTimestamp,
    int pathTimeInMs,
    bool hasTickets)
{
  Train train;

  train.setIndex(index);
  train.setDestination(destination);
  train.setDepartureTimestamp(depatureTimestamp);
  train.setPathTimeInMs(pathTimeInMs);
  train.setHasTickets(hasTickets);

  list.pushBack(train);
}

Train *TrainORM::getTrainByIndex(int index)
{
  Item<Train> *iterator = list.getBegin();

  while (iterator != nullptr)
  {
    Train train = iterator->getData();

    if (train.getIndex() == index)
    {
      return &train;
    }

    iterator = iterator->getNext();
  }

  return nullptr;
}

LinkedList<Train> TrainORM::queryTrainsByDestinationAndTimeInterval(
    std::string destination,
    int fromTimestamp,
    int toTimestamp)
{
  LinkedList<Train> filteredTrainList;
  Item<Train> *iterator = list.getBegin();

  while (iterator != nullptr)
  {
    Train train = iterator->getData();

    std::string trainDestination = train.getDestination();
    int trainDeparture = train.getDepartureTimestamp();

    if (trainDestination == destination && trainDeparture >= fromTimestamp && trainDeparture <= toTimestamp)
    {
      filteredTrainList.pushBack(train);
    }

    iterator = iterator->getNext();
  }

  return filteredTrainList;
}
