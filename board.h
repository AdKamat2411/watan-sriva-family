#include "vertex.h"
#include "edge.h"
#include "tile.h"
#include "observer.h"
#include "dice.h"

class Board: public Observer {
    Vertex* vertices[54];
    Edge* edges[71];
    Tile* tiles[19];
    int currGeese;
    Dice* dice; 
    public:
        Board(Dice* dice, int currGeese = -1);
        void notify() override;
        void printBoard();
        void notifyTiles();
        void initializeBoard(); // sets resourceType and dieValue for each tile
};
