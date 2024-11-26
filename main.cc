#include "board.h"
#include "randomboardsetup.h"
using namespace std;

int main() {
    Dice* fairDice = new FairDice();
    Board board(fairDice);
    std::cout << "Setting up the board" << std::endl;
    RandomBoardSetup randomSetup;
    board.initializeBoard(randomSetup);
    std::cout << "\nPrinting all tiles and their values:" << std::endl;
    for (int i = 0; i < 19; ++i) {
        Tile* tile = board.getTile(i); 
        std::cout << "Tile " << i << ": "
                  << "Resource = " << tile->getResource()
                  << ", Die Value = " << (tile->getDieVal() == -1 ? "None" : std::to_string(tile->getDieVal()))
                  << std::endl;
    }
    cout << "Initial Board State:" << endl;
    board.printBoard();
    cout << "\nRolling the dice:" << endl;
    fairDice->roll();
    std::cout << "Dice rolled: " << fairDice->getSumOfRoll() << std::endl;
    delete fairDice;
    return 0;
}
