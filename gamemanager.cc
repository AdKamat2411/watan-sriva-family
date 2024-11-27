#include "gamemanager.h"
#include "randomboardsetup.h"
#include <iostream>
using namespace std;

GameManager::GameManager() : board(nullptr), dice(nullptr), currentTurn(0) {}

GameManager::~GameManager() {
  delete board;
  delete dice;
  for (auto player : players) {
    delete player;
  }
}

void GameManager::initializeGame() {
  dice = new FairDice();
  board = new Board(dice);
  RandomBoardSetup setup;
  board->initializeBoard(setup);
  initializePlayers();
}

void GameManager::initializePlayers() {
  std::vector<std::string> colors = {"Blue", "Red", "Orange", "Yellow"};
  for (int i = 0; i < 4; ++i) {
    Player* player = new Player(colors[i], i);
    players.push_back(player);
  }
}

void GameManager::initialPlacementPhase() {
  std::vector<int> placementOrder = {0, 1, 2, 3, 3, 2, 1, 0};
  for (int turn : placementOrder) {
    Player* currPlayer = players[turn];
    cout << "Student " << currPlayer->getColor()
      << ", where do you want to complete an Assignment? (Enter vertex index): " << endl;\
    int vertexIndex;
    bool validPlacement = false;
    while (!validPlacement) {
      cin >> vertexIndex;
      if (std::cin.fail() || vertexIndex < 0 || vertexIndex >= 53) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please enter a valid vertex index: " << endl;
      } else {
        Vertex* targetVertex = board->getVertex(vertexIndex);
        //to be fixed
        if (targetVertex->isAvailable() && currPlayer->buildCriterion(*targetVertex, nullptr, 0)) {
          validPlacement = true;
        } else {
          cout << "Vertex " << vertexIndex << " is not available. Choose another: " << endl;
        }
      }
    }
  }
  board->printBoard();
}

void GameManager::startGame() {
  cout << "Starting Game!" << endl;
  while (true) {
    Player* currentPlayer = players[currentTurn];
    playTurn(currentPlayer);

    if (checkVictory(currentPlayer)) {
        cout << "Player " << currentPlayer->getColor() << " wins!" << endl;
        break;
    }
    currentTurn = (currentTurn + 1) % players.size();
  }
}

void GameManager::playTurn(Player* player) {
  cout << "Student " << player->getColor() << "'s turn." << endl;

  bool diceRolled = false;

  while (!diceRolled) {
    cout << "Enter a command (load, fair, roll): ";
    string command;
    cin >> command;

    if (command == "load") {
      delete dice; 
      dice = DiceFactory::createDice(DiceType::Loaded);
      cout << "Loaded dice selected." << endl;
    } else if (command == "fair") {
      delete dice; 
      dice = DiceFactory::createDice(DiceType::Fair);
      cout << "Fair dice selected." << endl;
    } else if (command == "roll") {
      dice->roll();
      cout << "Dice rolled: " << dice->getSumOfRoll() << endl;
      board->notify(dice->getSumOfRoll());
      diceRolled = true;
    } else {
        cout << "Invalid command. Please enter 'load', 'fair', or 'roll'." << endl;
    }
  }
  
}

bool GameManager::checkVictory(Player* player) {
    return player->getVictoryPoints() >= 10; 
}