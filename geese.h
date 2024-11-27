#include <iostream>
#include "gamemanager.h"

class geese : public Observer {
    int currTile;
    public:
        geese(int currTile = -1);
        void moveGeese(int newTile, Tile** tileArr);
        void stealResource(GameManager* g);
};
