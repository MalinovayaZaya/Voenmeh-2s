#include "../train/train.h"
#include "../linkedList/linked_list.cpp"

#ifndef _TRAIN_ORM
#define _TRAIN_ORM

class TrainORM
{
private:
  std::string fileName;
  LinkedList<Train> list;

public:
  TrainORM();

  void addTrain(Train);

  Train* getTrainByIndex(int);

  LinkedList<Train>* getTrains();

  LinkedList<Train> queryTrainsByDestinationAndTimeInterval(std::string, int, int);

  void loadFromFile();

  void saveToFile();
};

#endif
