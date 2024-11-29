#include "gamemanager.h"
#include "randomboardsetup.h"
#include <iostream>
#include "board.h"
#include "savemanager.h"
#include <sstream>
#include "fileboardsetup.h"
#include <limits>
using namespace std;

GameManager::GameManager() : board(nullptr), dice(nullptr), currentTurn(0) {}

GameManager::~GameManager() = default; // Smart pointers handle cleanup.

void GameManager::initializeGame() {
    dice = std::make_shared<FairDice>();
    Geese = std::make_unique<geese>(-1);

    if (!board) { 
        board = std::make_shared<Board>(dice);
        RandomBoardSetup setup;
        board->initializeBoard(setup); 
    }
    board->printBoard();
    initializePlayers();
    initialPlacementPhase();
}

void GameManager::initializePlayers() {
    std::vector<std::string> colors = {"Blue", "Red", "Orange", "Yellow"};
    for (int i = 0; i < 4; ++i) {
        players.push_back(std::make_shared<Player>(colors[i], i));
    }
}

std::shared_ptr<Player> GameManager::findPlayerByColor(const std::string& color) {
    for (const auto& player : players) {
        if (player->getColor() == color) {
            return player;
        }
    }
    return nullptr; 
}

void GameManager::initialPlacementPhase() {
    std::vector<int> placementOrder = {0, 1, 2, 3, 3, 2, 1, 0};
    for (int turn : placementOrder) {
        auto currPlayer = players[turn];
        cout << "Student " << currPlayer->getColor()
             << ", where do you want to complete an Assignment? (Enter vertex index): " << endl;
        int vertexIndex;
        bool validPlacement = false;
        while (!validPlacement) {
            cin >> vertexIndex;
            if (std::cin.fail() || vertexIndex < 0 || vertexIndex > 53) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid vertex index: " << endl;
            } else {
                auto targetVertex = board->getVertex(vertexIndex);
                std::shared_ptr<Edge> sharedEdgePtrs[72];
                auto& edges = board->getEdges();
                for (size_t i = 0; i < edges.size(); ++i) {
                    sharedEdgePtrs[i] = edges[i]; // Direct assignment as edges are shared_ptr
                }
                if (targetVertex->isAvailable() && currPlayer->buildCriterion(*targetVertex, sharedEdgePtrs, 72)) {
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
        auto currentPlayer = players[currentTurn];
        playTurn(currentPlayer);

        if (checkVictory(currentPlayer)) {
            cout << "Player " << currentPlayer->getColor() << " wins!" << endl;
            break;
        }
        currentTurn = (currentTurn + 1) % players.size();
    }
}

void GameManager::playTurn(std::shared_ptr<Player> player) {
    cout << "Student " << player->getColor() << "'s turn." << endl;

    bool diceRolled = false;

    while (!diceRolled) {
        cout << "Enter a command (load, fair, roll): ";
        string dcommand;
        cin >> dcommand;

        if (dcommand == "load") {
            dice = std::make_shared<LoadedDice>();
            cout << "Loaded dice selected." << endl;
        } else if (dcommand == "fair") {
            dice = std::make_shared<FairDice>();
            cout << "Fair dice selected." << endl;
        } else if (dcommand == "roll") {
            std::vector<Player*> rawPlayerPtrs;
            for (const auto& player : players) {
                rawPlayerPtrs.push_back(player.get());
            }
            dice->roll(rawPlayerPtrs);
            cout << "Dice rolled: " << dice->getSumOfRoll() << endl;
            if (dice->getSumOfRoll() == 7) {
                Geese->stealResource(shared_from_this());
            } else {
                auto& tiles = board->getTiles();
                for (const auto& tile : tiles) {
                    if (tile) {
                        tile->notify(dice->getSumOfRoll(), rawPlayerPtrs, currentTurn);
                    }
                }
            }
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
                cout << p->getColor() << " has "
                     << p->getVictoryPoints() << " victory points, " 
                     << p->getResourceCount("CAFFEINE") << " caffeines, "
                     << p->getResourceCount("LAB") << " labs, "
                     << p->getResourceCount("LECTURE") << " lectures, "
                     << p->getResourceCount("TUTORIAL") << " tutorials, and "
                     << p->getResourceCount("STUDY") << " studies." << endl;
            }
        } else if (command == "next") {
            turnEnded = true;
            cout << "Turn ended for " << player->getColor() << "." << endl;
        } else if (command == "help") {
            cout << "Valid commands:\n"
                 << "board\n"
                 << "status\n"
                 << "next\n"
                 << "help\n";
        } else {
            cout << "Invalid command. Type 'help' for a list of valid commands." << endl;
        }
    }
}

bool GameManager::checkVictory(std::shared_ptr<Player> player) {
    return player->getVictoryPoints() >= 10; 
}

int GameManager::getcurrTurn() {
    return currentTurn;
}

std::shared_ptr<Board> GameManager::getBoard() { 
    return board; 
}

std::vector<std::shared_ptr<Player>> GameManager::getPlayers() { 
    return players; 
}

string GameManager::getCurrentPlayer() { 
    return players[currentTurn]->getColor(); 
}

void GameManager::loadGame(std::ifstream& inFile) {
    inFile >> currentTurn;
    std::vector<std::string> colors = {"Blue", "Red", "Orange", "Yellow"};
    players.clear();

    // Create players using smart pointers
    for (int i = 0; i < 4; ++i) {
        players.push_back(std::make_shared<Player>(colors[i], i));
    }

    // Initialize dice and board with smart pointers
    dice = std::make_shared<FairDice>();
    board = std::make_shared<Board>(dice);

    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (auto& player : players) {
        int resourceCounts[5];
        std::string color = player->getColor();
        int victoryPoints = 0;
        std::vector<int> goals;
        std::vector<std::pair<int, int>> criteria;

        std::string line;
        std::getline(inFile, line);
        std::istringstream lineStream(line);

        for (int i = 0; i < 5; ++i) {
            lineStream >> resourceCounts[i];
        }

        char g, c;
        lineStream >> g;
        if (g == 'g') {
            int value;
            while (lineStream >> value) {
                goals.emplace_back(value);
                auto arr = board->getEdges();
                arr[value]->setOwner(player->getColor());
            }
            lineStream.clear();
            lineStream >> c;
        }

        if (c == 'c') {
            int criterionNumber, completionLevel;
            while (lineStream >> criterionNumber >> completionLevel) {
                criteria.emplace_back(criterionNumber, completionLevel);
                auto arr = board->getVertices();
                arr[criterionNumber]->setOwner(player->getColor());
                if (completionLevel == 1) {
                    victoryPoints += 1;
                    arr[criterionNumber]->setHouseLevel("Assignment");
                } else if (completionLevel == 2) {
                    victoryPoints += 2;
                    arr[criterionNumber]->setHouseLevel("Midterm");
                } else if (completionLevel == 3) {
                    victoryPoints += 3;
                    arr[criterionNumber]->setHouseLevel("Exam");
                }
            }
        }

        // Update the player's state
        player->loadState(resourceCounts, color, victoryPoints, goals, criteria);
    }

    // Load tiles data
    std::vector<std::pair<std::string, int>> tilesData;
    std::string line;
    std::getline(inFile, line);
    std::istringstream lineStream(line);

    for (int i = 0; i < 19; ++i) {
        int resourceId, dieValue;
        lineStream >> resourceId >> dieValue;

        std::string resourceType;
        switch (resourceId) {
            case 0: resourceType = "CAFFEINE"; break;
            case 1: resourceType = "LAB"; break;
            case 2: resourceType = "LECTURE"; break;
            case 3: resourceType = "STUDY"; break;
            case 4: resourceType = "TUTORIAL"; break;
            case 5: resourceType = "NETFLIX"; break;
            default:
                std::cerr << "Error: Invalid resource ID " << resourceId << std::endl;
                return;
        }

        tilesData.emplace_back(resourceType, dieValue);
    }

    board->loadState(tilesData);

    // Load geese state
    int geeseTile;
    inFile >> geeseTile;
    Geese = std::make_unique<geese>();
    Geese->moveGeese(geeseTile, board->getTiles());

    cout << "Game loaded successfully!" << endl;
}


void GameManager::loadBoard(std::ifstream& inFile) {
    dice = std::make_shared<FairDice>();
    board = std::make_shared<Board>(dice);
    FileBoardSetup fileSetup(inFile);
    fileSetup.setup(*board);
    cout << "Board loaded successfully from file." << endl;
}
