#include "geese.h"
#include "gamemanager.h"
#include <limits>
#include <algorithm>
#include <array>

geese::geese(int currTile) : currTile(currTile) {}

void geese::moveGeese(int newTile, const std::array<std::unique_ptr<Tile>, 19>& tileArr) {
    if (currTile != -1) {
        tileArr[currTile]->updateGeese();
    }
    tileArr[newTile]->updateGeese();
    currTile = newTile;
}

void geese::stealResource(const std::shared_ptr<GameManager>& g) {
    auto players = g->getPlayers();

    for (auto& player : players) {
        int totalResources = 0;
        std::vector<std::string> resourceNames = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL"};
        std::vector<int> resourceCounts;

        for (const std::string& resource : resourceNames) {
            int count = player->getResourceCount(resource);
            resourceCounts.push_back(count);
            totalResources += count;
        }

        if (totalResources >= 10) {
            int resourcesToLose = totalResources / 2;
            std::cout << "Student " << player->getColor() << " loses " 
                      << resourcesToLose << " resources to the geese. They lose:" << std::endl;

            std::vector<int> lostResources(resourceCounts.size(), 0);
            std::vector<int> cumulativeProbabilities;
            int runningTotal = 0;

            for (int count : resourceCounts) {
                runningTotal += count;
                cumulativeProbabilities.push_back(runningTotal);
            }

            for (int i = 0; i < resourcesToLose; ++i) {
                int randomValue = rand() % totalResources + 1;
                for (size_t j = 0; j < cumulativeProbabilities.size(); ++j) {
                    if (randomValue <= cumulativeProbabilities[j]) {
                        player->removeResources(resourceNames[j], 1);
                        lostResources[j]++;
                        totalResources--;
                        resourceCounts[j]--;
                        break;
                    }
                }
            }

            for (size_t i = 0; i < lostResources.size(); ++i) {
                if (lostResources[i] > 0) {
                    std::cout << lostResources[i] << " " << resourceNames[i] << std::endl;
                }
            }
        }
    }

    std::cout << "Choose where to place the GEESE." << std::endl;
    int geeseTile;
    std::cin >> geeseTile;

    std::string currPlayer = g->getCurrentPlayer();

    Player* currentPlayer = nullptr;
    for (auto& player : players) {
        if (currPlayer == player->getColor()) {
            currentPlayer = player.get();
            break;
        }
    }

    std::vector<std::string> playersOnTile;
    auto tile = g->getBoard()->getTile(geeseTile);
    auto vertArr = tile->getAdjacentVertices();

    for (int i = 0; i < 6; i++) {
        if (!vertArr[i]->isAvailable()) {
            playersOnTile.push_back(vertArr[i]->getName());
        }
    }

    if (playersOnTile.empty()) {
        std::cout << "Student " << currPlayer << " has no students to steal from." << std::endl;
        return;
    }

    for (const std::string& p : playersOnTile) {
        std::cout << "Student " << currPlayer << " can choose to steal from " << p << "." << std::endl;
    }

    std::cout << "Choose a student to steal from." << std::endl;

    std::string targetPlayer;
    while (true) {
        std::cin >> targetPlayer;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid player." << std::endl;
            continue;
        }
        if (std::find(playersOnTile.begin(), playersOnTile.end(), targetPlayer) != playersOnTile.end()) {
            break;
        }

        std::cout << "Invalid choice. Please choose a valid student to steal from: ";
    }

    Player* target = nullptr;
    for (auto& player : players) {
        if (targetPlayer == player->getColor()) {
            target = player.get();
            break;
        }
    }

    int totalResources = 0;
    std::vector<std::string> resourceNames = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL"};
    for (const std::string& resource : resourceNames) {
        totalResources += target->getResourceCount(resource);
    }

    if (totalResources == 0) {
        std::cout << "Student " << targetPlayer << " has no resources to steal." << std::endl;
        return;
    }

    std::vector<int> cumulativeProbabilities;
    int runningTotal = 0;
    for (const std::string& resource : resourceNames) {
        runningTotal += target->getResourceCount(resource);
        cumulativeProbabilities.push_back(runningTotal);
    }

    int randomValue = rand() % totalResources + 1;

    std::string stolenResource;
    for (size_t i = 0; i < cumulativeProbabilities.size(); ++i) {
        if (randomValue <= cumulativeProbabilities[i]) {
            stolenResource = resourceNames[i];
            break;
        }
    }

    target->removeResources(stolenResource, 1);
    currentPlayer->addResources(stolenResource, 1);

    std::cout << "Student " << currPlayer << " steals " << stolenResource << " from student " << targetPlayer << "." << std::endl;

    moveGeese(geeseTile, g->getBoard()->getTiles());
}
