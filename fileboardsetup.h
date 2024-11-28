#ifndef FILEBOARDSETUP_H
#define FILEBOARDSETUP_H

#include "boardsetup.h"
#include <fstream>
#include <string>
#include "board.h"

class FileBoardSetup : public BoardSetup {
    std::ifstream& inFile;

public:
    FileBoardSetup(std::ifstream& inFile);
    void assignResources(Board& board) override;
};

#endif
