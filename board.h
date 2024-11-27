#ifndef BOARD_H
#define BOARD_H

#include "vertex.h"
#include "edge.h"
#include "tile.h"
#include "subject.h"
#include "observer.h"
#include "dice.h"

class BoardSetup;

class Board: public Subject, public Observer {
    Vertex* vertices[54];
    Edge* edges[72];
    int currGeese;
    Dice* dice; 
    Tile* tiles[19];
    public:
        static const int vertArr[19][6];
        static const int edgeArr[19][6];

        Board(Dice* dice, int currGeese = -1);
        void notify(int rollSum = -1) override;
        void printBoard();
        void notifyTiles(int rollSum);
        void initializeBoard(BoardSetup& setupStrategy); // sets resourceType and dieValue for each tile
        Tile* getTile(int index) const;
        ~Board() noexcept;
        int* getVerticesConnectedToEdge(int edge);
        Vertex* getVertex(int index) const;
};

#endif
