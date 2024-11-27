#include "randomboardsetup.h"
#include "board.h" 
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

RandomBoardSetup::RandomBoardSetup() {
  srand(time(nullptr));
}

void RandomBoardSetup::assignResources(Board& board) {
  std::vector<std::string> resources = {
    "TUTORIAL", "TUTORIAL", "TUTORIAL",
    "STUDY", "STUDY", "STUDY",
    "CAFFEINE", "CAFFEINE", "CAFFEINE", "CAFFEINE",
    "LAB", "LAB", "LAB", "LAB",
    "LECTURE", "LECTURE", "LECTURE", "LECTURE",
    "NETFLIX"
  };
  std::vector<int> diceValues = {
    2, 12,
    3, 3, 4, 4, 5, 5, 6, 6, 
    8, 8, 9, 9, 10, 10, 11, 11 
  };

  for (int i = 0; i < 19; ++i) {
    std::cout << "Processing tile" << i << "..." << std::endl;
    Tile* tile = board.getTile(i);
    int resourceIndex = rand() % resources.size();
    string selectedResource = resources[resourceIndex];
    tile->setResource(selectedResource);
    resources.erase(resources.begin() + resourceIndex);
    if (selectedResource == "NETFLIX") {
      tile->setDieVal(-1); 
    } else {
      int randomIndex = rand() % diceValues.size();
      tile->setDieVal(diceValues[randomIndex]);
      diceValues.erase(diceValues.begin() + randomIndex);           
    }
  }
}
