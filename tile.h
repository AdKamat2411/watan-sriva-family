#ifndef TILE_H
#define TILE_H

#include "vertex.h"
#include "edge.h"
#include <string>
#include "observer.h"
#include "player.h"

class Tile : public Observer {
    string resourceType;
    int dieValue;
    bool geeseFlag;
    Vertex* adjacentVert[6];
    Edge* adjacentEdge[6];
    public:
        Tile(Vertex** adjacentVert, Edge** adjacentEdge, string resourceType = "", int dieValue = -1, bool geeseFlag = false);
        void distributeResources(std::vector<Player*>& players);
        void updateGeese();
        int getDieVal();
        string getResource();
        void setResource(const std::string& resource);
        void setDieVal(int value);
        void notify(int rollSum, std::vector<Player*>& players, int currTurn) override;
};

#endif 
