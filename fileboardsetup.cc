#include "fileboardsetup.h"
#include <iostream>
#include <stdexcept>

FileBoardSetup::FileBoardSetup(std::ifstream& inFile) : inFile(inFile) {}

void FileBoardSetup::assignResources(Board& board) {
    for (int i = 0; i < 19; ++i) {
        int resourceId, dieValue;
        inFile >> resourceId >> dieValue;

        std::string resourceType;
        switch (resourceId) {
            case 0: resourceType = "CAFFEINE"; break;
            case 1: resourceType = "LAB"; break;
            case 2: resourceType = "LECTURE"; break;
            case 3: resourceType = "STUDY"; break;
            case 4: resourceType = "TUTORIAL"; break;
            case 5: resourceType = "NETFLIX"; break;
            default:
                std::cerr << "Error: Invalid resource ID " << resourceId << std::endl;
                return;
        }
        Tile* tile = board.getTile(i);
        tile->setResource(resourceType);
        tile->setDieVal(dieValue);
    }

    std::cout << "Board setup successfully loaded from file" << std::endl;
}
