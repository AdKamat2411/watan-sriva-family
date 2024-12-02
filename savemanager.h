#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "gamemanager.h"
#include <fstream>
#include <string>
#include <vector>

class SaveManager {
public:
    void saveGame(const std::string& filename, std::shared_ptr<GameManager> gameManager);
};

#endif 
