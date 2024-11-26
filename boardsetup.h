#ifndef BOARDSETUP_H
#define BOARDSETUP_H
#include "board.h"

class BoardSetup {
  public:
    void setup (Board& board) {
      assignResources(board);     
      finalizeSetup(board);   
    }
    virtual void assignResources(Board& board) = 0;
    virtual void finalizeSetup(Board& board) {}
    virtual ~BoardSetup() = default;
};

#endif
