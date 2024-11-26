#include "vertex.h"
#include "edge.h"
#include "tile.h"

class Board {
    Vertex* vertices[54];
    Edge* edges[71];
    Tile* tiles[19];
    int currGeese;
    public:
        Board(int currGeese = -1);
        void printBoard();
        void notifyTiles();
        void initializeBoard(); // sets resourceType and dieValue for each tile
};
