#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
 public:
  virtual void notify(int rollSum = -1) = 0;
  virtual ~Observer() = default;
};

#endif
