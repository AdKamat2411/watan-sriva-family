#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <memory> // Include for std::unique_ptr
#include "subject.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Player;

class Dice : public Subject {
  protected:
    int sumOfRoll;
  public:
    Dice() : sumOfRoll(0) {}
    virtual ~Dice() {}
    virtual void roll(std::vector<Player*>& players) = 0;
    int getSumOfRoll() const { return sumOfRoll; }
};

class FairDice : public Dice {
  public:
    FairDice() { srand(time(nullptr)); }
    void roll(std::vector<Player*>& players) override { 
      sumOfRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
      notifyObservers(sumOfRoll, players, 0); 
    }
};

class LoadedDice : public Dice {
  public:
    void roll(std::vector<Player*>& players) override { 
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
      notifyObservers(sumOfRoll, players, 0); 
    }
};

enum class DiceType { Fair, Loaded };

class DiceFactory {
  public:
    static std::unique_ptr<Dice> createDice(DiceType type) {
      if (type == DiceType::Fair) {
        return std::make_unique<FairDice>();
      } else if (type == DiceType::Loaded) {
        return std::make_unique<LoadedDice>();
      }
      return nullptr;
    }
};

#endif
