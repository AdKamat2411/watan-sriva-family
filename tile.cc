#include "tile.h"
#include <iostream>
using namespace std;

Tile::Tile(Vertex** vertArr, Edge** edgeArr, string resourceType, int dieValue, bool geeseFlag):
    resourceType(resourceType), dieValue(dieValue), geeseFlag(geeseFlag) {
        for (int i = 0; i < 6; i++) {
            adjacentVert[i] = vertArr[i];
            adjacentEdge[i] = edgeArr[i];
        }
    }

void Tile::updateGeese() { geeseFlag = !geeseFlag;}

int Tile::getDieVal() { return dieValue; }

string Tile::getResource() { return resourceType; }

void Tile::distributeResources(std::vector<Player*>& players) {
    for (int i = 0; i < 6; ++i) {
        Vertex* vertex = adjacentVert[i];
        if (vertex && !vertex->getName().empty()) { 
            for (auto& player : players) {
                if (player->getColor() == vertex->getName()) {
                    player->addResources(resourceType, 1);
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

Vertex** Tile::getAdjacentVertices() { return adjacentVert; }


bool Tile::isGeese() { return updateGeese; }
