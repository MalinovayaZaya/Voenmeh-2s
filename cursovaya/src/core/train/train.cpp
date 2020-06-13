#include <cstring>

#include "train.h"

Train::Train() {}

int Train::getIndex()
{
  return index;
}

void Train::setIndex(int _index)
{
  index = _index;
}

std::string Train::getDestination()
{
  return std::string(dest);
}

void Train::setDestination(std::string _dest)
{
  _dest.copy(dest, 4, 0);
}

int Train::getDepartureTimestamp()
{
  return departureTimestamp;
}

void Train::setDepartureTimestamp(int timestamp)
{
  departureTimestamp = timestamp;
}

int Train::getPathTimeInMs()
{
  return pathTime;
}

void Train::setPathTimeInMs(int _pathTime)
{
  pathTime = _pathTime;
}

bool Train::getHasTickets()
{
  return hasTickets;
}

void Train::setHasTickets(bool _hasTickets)
{
  hasTickets = _hasTickets;
}
