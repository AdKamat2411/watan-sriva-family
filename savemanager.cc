#include "savemanager.h"
#include <memory>
#include <stdexcept>

void SaveManager::saveGame(const std::string& filename, std::shared_ptr<GameManager> gameManager) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving game.");
    }

    // Save current turn
    outFile << gameManager->getcurrTurn() << std::endl;

    // Save players' resources and state
    for (const auto& player : gameManager->getPlayers()) {
        outFile << player->getResourceCount("CAFFEINE") << " "
                << player->getResourceCount("LAB") << " "
                << player->getResourceCount("LECTURE") << " "
                << player->getResourceCount("STUDY") << " "
                << player->getResourceCount("TUTORIAL") << " ";

        outFile << "g ";

        auto& edgeArr = gameManager->getBoard()->getEdges();
        for (size_t i = 0; i < edgeArr.size(); i++) {
            if (edgeArr[i]->getName() == player->getColor()) {
                outFile << edgeArr[i]->getIdx() << " ";
            }
        }

        outFile << "c ";
        auto& vertArr = gameManager->getBoard()->getVertices();
        for (size_t i = 0; i < vertArr.size(); i++) {
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

    // Save board tiles
    auto& tiles = gameManager->getBoard()->getTiles();
    for (size_t i = 0; i < tiles.size(); ++i) {
        const auto& tile = tiles[i];
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

    // Save geese tile
    int geeseTile = -1;
    for (size_t i = 0; i < tiles.size(); ++i) {
        if (tiles[i]->isGeese()) {
            geeseTile = i;
            break;
        }
    }

    if (geeseTile == -1) {
        for (size_t i = 0; i < tiles.size(); ++i) {
            if (tiles[i]->getResource() == "NETFLIX") {
                geeseTile = i;
                break;
            }
        }
    }

    outFile << geeseTile << std::endl; 

    outFile.close();
}
