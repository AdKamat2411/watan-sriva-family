#ifndef GEESE_H
#define GEESE_H

#include <iostream>
#include "tile.h"
class GameManager;

class geese {
    int currTile;
    public:
        geese(int currTile = -1);
        void moveGeese(int newTile, Tile** tileArr);
        void stealResource(GameManager* g);
};

#endif