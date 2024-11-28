#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "dice.h"
#include "player.h"
#include <vector>
#include "geese.h"
#include <fstream>

class GameManager {
  private:
    Board* board; 
    Dice* dice;
    geese* Geese;
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
    Board* getBoard();
    std::vector<Player*> getPlayers();
    string getCurrentPlayer();
    int getcurrTurn();
    void loadGame(std::ifstream& inFile);
    void loadBoard(std::ifstream& inFile);
};

#endif
