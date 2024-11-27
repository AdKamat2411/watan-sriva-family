#include "gamemanager.h"
#include "randomboardsetup.h"
#include <iostream>
#include "board.h"
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
  board->printBoard();
  initializePlayers();
  initialPlacementPhase();
}

void GameManager::initializePlayers() {
  std::vector<std::string> colors = {"Blue", "Red", "Orange", "Yellow"};
  for (int i = 0; i < 4; ++i) {
    Player* player = new Player(colors[i], i);
    players.push_back(player);
  }
}

Player* GameManager::findPlayerByColor(const std::string& color) {
    for (Player* player : players) {
        if (player->getColor() == color) {
            return player;
        }
    }
    return nullptr; 
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
        if (targetVertex->isAvailable() && currPlayer->buildCriterion(*targetVertex, board->getEdges(), 72)) {
          validPlacement = true;
        } else {
          cout << "Vertex " << vertexIndex << " is not available. Choose another: " << endl;
        }
      }
      board->printBoard();
    }
  }
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
    string dcommand;
    cin >> dcommand;

    if (dcommand == "load") {
      delete dice; 
      dice = DiceFactory::createDice(DiceType::Loaded);
      cout << "Loaded dice selected." << endl;
    } else if (dcommand == "fair") {
      delete dice; 
      dice = DiceFactory::createDice(DiceType::Fair);
      cout << "Fair dice selected." << endl;
    } else if (dcommand == "roll") {
      dice->roll();
      cout << "Dice rolled: " << dice->getSumOfRoll() << endl;
      board->notify(dice->getSumOfRoll());
      diceRolled = true;
    } else {
        cout << "Invalid command. Please enter 'load', 'fair', or 'roll'." << endl;
    }
  }
  bool turnEnded = false;
  string command;
  while (!turnEnded) {
    cout << "Enter a command: ";
    cin >> command;

    if (command == "board") {
        board->printBoard();
    } else if (command == "status") {
        for (const auto& p : players) {
            cout << p->getColor() << ": "
                << p->getVictoryPoints() << " VP, Resources: ";
            for (const string& resource : {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL"}) {
                cout << resource << "=" << p->getResourceCount(resource) << " ";
            }
            cout << endl;
        }
    } else if (command == "criteria") {
        Vertex** allVertices = board->getVertices();
        player->printCompletions(allVertices, 54);
    } else if (command == "achieve") {
        int goalNumber;
        cin >> goalNumber;
        Edge** allEdges = board->getEdges();

        if (goalNumber < 0 || goalNumber >= 72) {
            cout << "Invalid goal number. Please enter a value between 0 and 71." << endl;
        } else {
            Edge* goalEdge = allEdges[goalNumber];
            if (player->claimEdge(*goalEdge, allEdges, 72)) {
                cout << "Achieved goal " << goalNumber << "." << endl;
            } else {
                cout << "Failed to achieve goal " << goalNumber << "." << endl;
            }
        }
    } else if (command == "complete") {
        int criterionNumber;
        cin >> criterionNumber;
        Vertex** allVertices = board->getVertices();

        if (criterionNumber < 0 || criterionNumber >= 54) {
            cout << "Invalid criterion number. Please enter a value between 0 and 53." << endl;
        } else {
            Vertex* targetVertex = allVertices[criterionNumber];
            if (player->buildCriterion(*targetVertex, nullptr, 0)) {
                cout << "Completed criterion " << criterionNumber << "." << endl;
            } else {
                cout << "Failed to complete criterion " << criterionNumber << "." << endl;
            }
        }
    } else if (command == "improve") {
        int criterionNumber;
        cin >> criterionNumber;
        Vertex** allVertices = board->getVertices();

        if (criterionNumber < 0 || criterionNumber >= 54) {
            cout << "Invalid criterion number. Please enter a value between 0 and 53." << endl;
        } else {
            Vertex* targetVertex = allVertices[criterionNumber];
            if (player->upgradeCriterion(*targetVertex)) {
                cout << "Improved criterion " << criterionNumber << "." << endl;
            } else {
                cout << "Failed to improve criterion " << criterionNumber << "." << endl;
            }
        }
    } else if (command == "trade") {
        string targetColor, give, take;
        cin >> targetColor >> give >> take;
        Player* targetPlayer = findPlayerByColor(targetColor); 
        if (targetPlayer) {
            if (Player::trade(*player, *targetPlayer, give, take)) {
                cout << "Trade with " << targetColor << " successful." << endl;
            } else {
                cout << "Trade with " << targetColor << " failed." << endl;
            }
        } else {
            cout << "Player " << targetColor << " not found." << endl;
        }
    // } else if (command == "save") {
    //     string filename;
    //     cin >> filename;
    //     saveGame(filename); // Assuming saveGame is implemented
    //     cout << "Game saved to " << filename << "." << endl;
    } else if (command == "next") {
        turnEnded = true;
        cout << "Turn ended for " << player->getColor() << "." << endl;
    } else if (command == "help") {
        cout << "Valid commands:\n"
            << "board\n"
            << "status\n"
            << "criteria\n"
            << "achieve <goal>\n"
            << "complete <criterion>\n"
            << "improve <criterion>\n"
            << "trade <colour> <give> <take>\n"
            << "next\n"
            << "save <file>\n"
            << "help\n";
    } else {
        cout << "Invalid command. Type 'help' for a list of valid commands." << endl;
    }
  }
}

bool GameManager::checkVictory(Player* player) {
    return player->getVictoryPoints() >= 10; 
}

Board* GameManager::getBoard() { return board; }

std::vector<Player*> GameManager::getPlayers() { return players; }

string GameManager::getCurrentPlayer() { return players[currentTurn]->getColor(); }

