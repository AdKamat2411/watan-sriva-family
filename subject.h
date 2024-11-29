#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory> // For std::shared_ptr

class Player;
class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers; // Use smart pointers
 public:
  void attach(std::shared_ptr<Observer> o); // Accept shared_ptr
  void detach(std::shared_ptr<Observer> o); // Accept shared_ptr
  void notifyObservers(int rollSum, std::vector<Player*>& players, int currTurn);
  virtual ~Subject() = default;
  std::vector<std::shared_ptr<Observer>> getObservers(); // Return smart pointers
};

#endif
