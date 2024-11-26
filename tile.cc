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
}


