#include "savemanager.h"

void SaveManager::saveGame(const std::string& filename, GameManager* gameManager) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving game.");
    }

    // Save current turn
    outFile << gameManager->getcurrTurn() << std::endl;

    // Save each player's data
    for (Player* player : gameManager->getPlayers()) {
        // Save resources
        outFile << player->getResourceCount("CAFFEINE") << " "
                << player->getResourceCount("LAB") << " "
                << player->getResourceCount("LECTURE") << " "
                << player->getResourceCount("STUDY") << " "
                << player->getResourceCount("TUTORIAL") << " ";

        // Save goals
        outFile << "g ";

        Edge** edgeArr = gameManager->getBoard()->getEdges();
        for (int i = 0; i < 72; i++) {
            if (edgeArr[i]->getName() == player->getColor()) {
                outFile << edgeArr[i]->getIdx() << " ";
            }
        }

        // Save criteria
        outFile << "c ";
        Vertex** vertArr = gameManager->getBoard()->getVertices();
        for (int i = 0; i < 54; i++) {
            if (vertArr[i]->getName() == player->getColor()) {
                outFile << vertArr[i]->getIdx() << " ";
                if (vertArr[i]->getHouseLevel() == "Assignment") {
                    outFile << "1 ";
                } else if (vertArr[i]->getHouseLevel() == "Midterm") {
                    outFile << "2 ";
                } else if (vertArr[i]->getHouseLevel() == "Exam") {
                    outFile << "3 ";
                }
            }
        }
        outFile << std::endl;
    }

    // Save board data
    Board* board = gameManager->getBoard();
    Tile** tiles = board->getTiles();
    for (int i = 0; i < 19; ++i) {
        Tile* tile = tiles[i];
        int resourceValue = tile->getDieVal();
        std::string resourceType = tile->getResource();
        
        int resourceIndex;
        if (resourceType == "CAFFEINE") resourceIndex = 0;
        else if (resourceType == "LAB") resourceIndex = 1;
        else if (resourceType == "LECTURE") resourceIndex = 2;
        else if (resourceType == "STUDY") resourceIndex = 3;
        else if (resourceType == "TUTORIAL") resourceIndex = 4;
        else if (resourceType == "NETFLIX") resourceIndex = 5;
        else throw std::runtime_error("Unknown resource type!");

        outFile << resourceIndex << " " << resourceValue << " ";
    }
    outFile << std::endl;

    // Save geese position
    int geeseTile;
    for (int i = 0; i < 19; i ++) {
        if (tiles[i]->isGeese()) {
            geeseTile = i;
            break;
        }
    }
    outFile << geeseTile << std::endl; // Assuming the board tracks which tile has the geese

    outFile.close();
}
