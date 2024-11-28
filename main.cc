#include <iostream>
#include <fstream>
#include "gamemanager.h"

using namespace std;

int main(int argc, char* argv[]) {
    GameManager gameManager;
    bool gameLoaded = false;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-seed" && i + 1 < argc) {
            int seed = stoi(argv[i + 1]);
            srand(seed); 
            cout << "Random seed set to: " << seed << endl;
            ++i;
        } else if (arg == "-load" && i + 1 < argc) {
            string fileName = argv[i + 1];
            ifstream inFile(fileName);
            if (!inFile) {
                cerr << "Error: Unable to open file " << fileName << endl;
                return 1;
            }
            gameManager.loadGame(inFile); 
            cout << "Game loaded from: " << fileName << endl;
            gameLoaded = true;
            ++i;
        } else if (arg == "-board" && i + 1 < argc) {
            string fileName = argv[i + 1];
            ifstream inFile(fileName);
            if (!inFile) {
                cerr << "Error: Unable to open board file " << fileName << endl;
                return 1;
            }
            gameManager.loadBoard(inFile); 
            cout << "Custom board loaded from: " << fileName << endl;
            ++i;
        } else {
            cerr << "Unknown or incomplete command-line option: " << arg << endl;
            return 1;
        }
    }


    if (!gameLoaded) {
        gameManager.initializeGame();
    }
    gameManager.startGame();

    return 0;
}
