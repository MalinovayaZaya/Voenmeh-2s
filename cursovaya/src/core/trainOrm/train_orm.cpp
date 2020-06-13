#include <iostream>
#include <fstream>
#include <cstring>
#include "train_orm.h"

TrainORM::TrainORM()
{
  fileName = "db.dat";

  loadFromFile();
}

void TrainORM::addTrain(Train train)
{
  list.pushBack(train);

  saveToFile();
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

LinkedList<Train> *TrainORM::getTrains()
{
  return &list;
}

LinkedList<Train>* TrainORM::queryTrainsByDestinationAndTimeInterval(
    std::string destination,
    int fromTimestamp,
    int toTimestamp)
{
  LinkedList<Train>* filteredTrainList = new LinkedList<Train>();
  Item<Train> *iterator = list.getBegin();

  while (iterator != nullptr)
  {
    Train train = iterator->getData();

    std::string trainDestination = train.getDestination();
    int trainDeparture = train.getDepartureTimestamp();

    if (trainDestination == destination && trainDeparture >= fromTimestamp && trainDeparture <= toTimestamp)
    {
      filteredTrainList->pushBack(train);
    }

    iterator = iterator->getNext();
  }

  return filteredTrainList;
}

struct TrainMask
{
  int index;
  char dest[4];
  int departureTimestamp;
  int pathTime;
  bool hasTickets;
};

void TrainORM::loadFromFile()
{
  std::ifstream input;
  input.open(fileName);
  TrainMask mask;

  while (input.read((char *)&mask, TRAIN_BYTE_SIZE))
  {
    Train train;
    
    train.setIndex(mask.index);
    train.setDestination(std::string(mask.dest));
    train.setDepartureTimestamp(mask.departureTimestamp);
    train.setPathTimeInMs(mask.pathTime);
    train.setHasTickets(mask.hasTickets);

    list.pushBack(train);
  }

  input.close();
}

void TrainORM::saveToFile()
{
  std::ofstream output;
  output.open(fileName);
  Item<Train>* iterator = list.getBegin();

  while (iterator != nullptr)
  {
    Train train = iterator->getData();
    TrainMask mask;

    mask.index = train.getIndex();
    strcpy(mask.dest, train.getDestination().c_str());
    mask.departureTimestamp = train.getDepartureTimestamp();
    mask.pathTime = train.getPathTimeInMs();
    mask.hasTickets = train.getHasTickets();

    output.write((char *)&mask, TRAIN_BYTE_SIZE);

    iterator = iterator->getNext();
  }

  output.close();
}
