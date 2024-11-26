#ifndef DICE_H
#define DICE_H

#include <iostream>
#include "subject.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Dice : public Subject {
  protected:
    int sumOfRoll;
  public:
    Dice() : sumOfRoll(0) {}
    virtual ~Dice() {}
    virtual void roll() = 0;
    int getSumOfRoll() const { return sumOfRoll; }
};

class FairDice : public Dice {
  public:
    FairDice() { srand(time(nullptr)); }
    void roll() override {
      sumOfRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
      notifyObservers();
    }
};

class LoadedDice : public Dice {
  public:
    void roll() override {
      int inputRoll = 0;
      bool validInput = false;
      while (!validInput) {
        cout << "Input a roll between 2 and 12: ";
        cin >> inputRoll;
        if (std::cin.fail() || inputRoll < 2 || inputRoll > 12) {
          cin.clear();
          cin.ignore();
          cout << "Invalid roll." << endl;
        } else {
          validInput = true;
        }
      }
      sumOfRoll = inputRoll;
      notifyObservers();
    }
};

enum class DiceType { Fair, Loaded };

class DiceFactory {
  public:
    static Dice* createDice(DiceType type) {
      if (type == DiceType::Fair) {
        return new FairDice();
      } else if (type == DiceType::Loaded) {
        return new LoadedDice();
      }
      return nullptr;
    }
};

#endif
