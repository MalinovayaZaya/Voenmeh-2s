#include "train_orm.h"

TrainORM::TrainORM() {
  Train test;

  test.setIndex(0);
  test.setDestination("MSK");
  test.setDepartureTimestamp(100);
  test.setPathTimeInMs(100);
  test.setHasTickets(true);

  list.pushBack(test);
}

void TrainORM::addTrain(Train train){
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

LinkedList<Train>* TrainORM::getTrains()
{
  return &list;
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
