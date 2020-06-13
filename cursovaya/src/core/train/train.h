#include <string>

#ifndef _TRAIN
#define _TRAIN

const int TRAIN_BYTE_SIZE = 18;

class Train
{
private:
  int index;
  char dest[4];
  int departureTimestamp;
  int pathTime;
  bool hasTickets;

public:
  Train();

  int getIndex();

  void setIndex(int);

  std::string getDestination();

  void setDestination(std::string);

  int getDepartureTimestamp();

  void setDepartureTimestamp(int);

  int getPathTimeInMs();
  
  void setPathTimeInMs(int);

  bool getHasTickets();

  void setHasTickets(bool);
};

#endif
