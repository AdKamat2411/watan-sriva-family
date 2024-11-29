#ifndef GEESE_H
#define GEESE_H

#include <iostream>
#include <array>
#include <memory>
#include "tile.h"

class GameManager;

class geese {
    int currTile;

public:
    geese(int currTile = -1);
    void moveGeese(int newTile, const std::array<std::unique_ptr<Tile>, 19>& tileArr);
    void stealResource(const std::shared_ptr<GameManager>& g);
};

#endif
