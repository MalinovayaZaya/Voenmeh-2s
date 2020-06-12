#ifndef _LINKED_LIST
#define _LINKED_LIST

template <typename T>
class Item
{
private:
  T data;
  Item *next;

public:
  Item();

  T getData();

  void setData(T data);

  Item* getNext();

  void setNext(Item* item);
};

template <typename T>
class LinkedList
{
private:
  Item<T>* begin;
  Item<T>* end;
  int count;

public:
  LinkedList();

  ~LinkedList();

  Item<T>* getBegin();

  Item<T>* getEnd();

  int getCount();

  void pushBack(T data);

  void pushFront(T data);

  T popBack();

  T popFront();
};

template <typename T>
Item<T>::Item()
{
  next = nullptr;
}

template <typename T>
T Item<T>::getData()
{
  return data;
}

template <typename T>
void Item<T>::setData(T _data)
{
  data = _data;
}

template <typename T>
Item<T> *Item<T>::getNext()
{
  return next;
}

template <typename T>
void Item<T>::setNext(Item<T> *_next)
{
  next = _next;
}

template <typename T>
LinkedList<T>::LinkedList()
{
  begin = nullptr;
  end = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  Item<T> *iterator;

  while(begin != nullptr)
  {
    iterator = begin;
    begin = begin->getNext();

    delete iterator;
  }
}

template <typename T>
Item<T>* LinkedList<T>::getBegin()
{
  return begin;
}

template <typename T>
Item<T>* LinkedList<T>::getEnd()
{
  return end;
}

template <typename T>
int LinkedList<T>::getCount()
{
  return count;
}

template <typename T>
void LinkedList<T>::pushBack(T data)
{
  Item<T>* item = new Item<T>();
  item->setData(data);
  
  if (begin == nullptr)
  {
    begin = item;
  }
  else
  {
    end->setNext(item);
  }
  
  end = item;
  count += 1;
}

template <typename T>
void LinkedList<T>::pushFront(T data)
{
  Item<T>* item = new Item<T>();
  item->setData(data);

  if (begin == nullptr)
  {
    begin = item;
  }
  else
  {
    Item<T>* next = begin;
    item->setNext(next);
    begin = item;
  }
  count += 1;
}

template <typename T>
T LinkedList<T>::popBack()
{
  Item<T>* iterator = begin;

  if (begin != end)
  {
    while (iterator->getNext() != end)
    {
      iterator = iterator->getNext();
    }
  }
  else
  {
    begin = nullptr;
    iterator = nullptr;
  }
  

  T data = end->getData();
  
  delete end;
  end = iterator;

  count -= 1;
  return data;
}

template <typename T>
T LinkedList<T>::popFront()
{
  T data = begin->getData();

  if (begin == end)
  {
    delete begin;

    begin = nullptr;
    end = nullptr;
  }
  else
  {
    Item<T>* next = begin->getNext();
    delete begin;
    begin = next;
  }

  count -= 1;
  return data;
}

#endif
