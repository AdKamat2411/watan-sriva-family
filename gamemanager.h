#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "dice.h"
#include "player.h"
#include <vector>
#include <memory>
#include "geese.h"
#include <fstream>

#include <memory>

class GameManager : public std::enable_shared_from_this<GameManager> {
  private:
    std::shared_ptr<Board> board;                // Use shared_ptr for Board
    std::shared_ptr<Dice> dice;                 // Use shared_ptr for Dice
    std::unique_ptr<geese> Geese;               // Use unique_ptr for geese
    std::vector<std::shared_ptr<Player>> players; // Use shared_ptr for players
    int currentTurn;

    void initializePlayers();
    void playTurn(std::shared_ptr<Player> player); // Accept shared_ptr
    bool checkVictory(std::shared_ptr<Player> player); // Accept shared_ptr
    void initialPlacementPhase();
    std::shared_ptr<Player> findPlayerByColor(const std::string& color); // Return shared_ptr
    
  public:
    GameManager();
    ~GameManager();
    void initializeGame();
    void startGame();
    std::shared_ptr<Board> getBoard();           // Return shared_ptr
    std::vector<std::shared_ptr<Player>> getPlayers(); // Return vector of shared_ptr
    std::string getCurrentPlayer();
    int getcurrTurn();
    void loadGame(std::ifstream& inFile);
    void loadBoard(std::ifstream& inFile);
};

#endif
