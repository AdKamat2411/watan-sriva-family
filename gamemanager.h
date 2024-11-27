#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "dice.h"
#include "player.h"
#include <vector>

class GameManager {
  private:
    Board* board; 
    Dice* dice;
    std::vector<Player*> players;
    int currentTurn;

    void initializePlayers();
    void playTurn(Player* player);
    bool checkVictory(Player* player);
    void initialPlacementPhase();
    Player* findPlayerByColor(const std::string& color);
    
  public:
    GameManager();
    ~GameManager();
    void initializeGame();
    void startGame();
    int getcurrTurn();
};

#endif
