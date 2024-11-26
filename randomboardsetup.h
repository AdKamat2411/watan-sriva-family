#ifndef RANDOMBOARDSETUP_H
#define RANDOMBOARDSETUP_H

#include "boardsetup.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "board.h"

class RandomBoardSetup : public BoardSetup {
public:
    RandomBoardSetup();
    void assignResources(Board& board) override;
};

#endif
