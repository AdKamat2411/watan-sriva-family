#include "tile.h"

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

void Tile::distributeResources() {
    std::cout << "Resources distributed for tile: " << resourceType << std::endl;
    std::cout << "Die Value distributed for tile: " << dieValue << std::endl;
}

void Tile::setResource(const std::string& resource) {
    resourceType = resource;
}

void Tile::setDieVal(int value) {
    dieValue = value;
}
