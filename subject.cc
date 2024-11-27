#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach( Observer* o ) {
  observers.emplace_back(o);
}

void Subject::detach( Observer* o ) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      delete o;
      break;
    }
  }
}

void Subject::notifyObservers(int rollSum, std::vector<Player*>& players, int currTurn) { 
    for (auto p : observers) {
        p->notify(rollSum, players, currTurn); 
    }
}

std::vector<Observer*> Subject::getObservers() {
  return observers;
}
