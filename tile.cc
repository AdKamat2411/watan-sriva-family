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

void Tile::distributeResources() {
    cout << "The tile in action is: " << endl;
    cout << "Resource type: " << resourceType << endl;
    cout << "Die Value: " << dieValue << endl;
    for (int i = 0; i < 6; ++i) {
        if (adjacentVert[i]->getName() != "") {
            cout << "Give resources to this person" << endl;
        }
    }
}

void Tile::setResource(const std::string& resource) {
    resourceType = resource;
}

void Tile::setDieVal(int value) {
    dieValue = value;
}

void Tile::notify(int rollSum) {
    if (rollSum == dieValue) { 
        distributeResources();
    }
}
