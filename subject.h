#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Player;

class Observer; // forward declaration

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers(int rollSum, std::vector<Player*>& players, int currTurn);
  virtual ~Subject() = default;
  std::vector<Observer*> getObservers();
};

#endif
