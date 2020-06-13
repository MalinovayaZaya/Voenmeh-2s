#include "../train/train.h"
#include "../linkedList/linked_list.cpp"

#ifndef _TRAIN_ORM
#define _TRAIN_ORM

class TrainORM
{
private:
  LinkedList<Train> list;

public:
  TrainORM();

  void addTrain(Train);

  Train* getTrainByIndex(int);

  LinkedList<Train>* getTrains();

  LinkedList<Train> queryTrainsByDestinationAndTimeInterval(std::string, int, int);
};

#endif
