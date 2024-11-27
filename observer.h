#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <vector>

class Player;

class Observer {
 public:
  virtual void notify(int rollSum, std::vector<Player*>& players, int currTurn) = 0;
  virtual ~Observer() = default;
};

#endif
