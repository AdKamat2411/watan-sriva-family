#ifndef BOARD_H
#define BOARD_H

#include "vertex.h"
#include "edge.h"
#include "tile.h"


class Board {
    Vertex* vertices[54];
    Edge* edges[72];
    Tile* tiles[19];
    int currGeese;
    public:
        static const int vertArr[19][6];
        static const int edgeArr[19][6];

        Board(int currGeese = -1);
        void printBoard();
        void notifyTiles();
        void initializeBoard(); // sets resourceType and dieValue for each tile
        ~Board();
};

#endif
