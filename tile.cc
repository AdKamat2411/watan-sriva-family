#include "tile.h"
#include <iostream>
using namespace std;

Tile::Tile(const std::array<std::shared_ptr<Vertex>, 6>& vertArr,
           const std::array<std::shared_ptr<Edge>, 6>& edgeArr,
           const std::string& resourceType, int dieValue, bool geeseFlag)
    : resourceType(resourceType), dieValue(dieValue), geeseFlag(geeseFlag),
      adjacentVert(vertArr), adjacentEdge(edgeArr) {}

void Tile::updateGeese() {
    geeseFlag = !geeseFlag;
}

int Tile::getDieVal() const {
    return dieValue;
}

std::string Tile::getResource() const {
    return resourceType;
}

void Tile::distributeResources(std::vector<Player*>& players) {
    for (const auto& vertex : adjacentVert) { // Use range-based for loop
        if (vertex && !vertex->getName().empty()) { // Check if vertex is valid and has an owner
            for (auto& player : players) {
                if (player->getColor() == vertex->getName()) {
                    int resourceAmount = 0;

                    if (vertex->getHouseLevel() == "Assignment") {
                        resourceAmount = 1;
                    } else if (vertex->getHouseLevel() == "Midterm") {
                        resourceAmount = 2;
                    } else if (vertex->getHouseLevel() == "Exam") {
                        resourceAmount = 3;
                    }
                    player->addResources(resourceType, resourceAmount);
                }
            }
        }
    }
}

void Tile::setResource(const std::string& resource) {
    resourceType = resource;
}

void Tile::setDieVal(int value) {
    dieValue = value;
}

void Tile::notify(int rollSum, std::vector<Player*>& players, int currTurn) {
    if (rollSum == dieValue) {
        distributeResources(players);
    }
}

const std::array<std::shared_ptr<Vertex>, 6>& Tile::getAdjacentVertices() const {
    return adjacentVert;
}

bool Tile::isGeese() const {
    return geeseFlag;
}
