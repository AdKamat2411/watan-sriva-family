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
        std::vector<int> goals = player->getGoals(); // Assuming getGoals() returns a vector of goal IDs
        for (int goal : goals) {
            outFile << goal << " ";
        }

        // Save criteria
        outFile << "c ";
        std::vector<std::pair<int, int>> criteria = player->getCriteria(); // Assuming getCriteria() returns pairs of {criterion number, completion number}
        for (const auto& criterion : criteria) {
            outFile << criterion.first << " " << criterion.second << " ";
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
