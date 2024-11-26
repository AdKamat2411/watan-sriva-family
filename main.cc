#include "board.h"
#include "randomboardsetup.h"
using namespace std;

int main() {
    Dice* fairDice = new FairDice();
    Board board(fairDice);
    std::cout << "Setting up the board" << std::endl;
    RandomBoardSetup randomSetup;
    board.initializeBoard(randomSetup);
    cout << "Initial Board State:" << endl;
    board.printBoard();
    cout << "\nRolling the dice:" << endl;
    fairDice->roll();
    std::cout << "Dice rolled: " << fairDice->getSumOfRoll() << std::endl;
    delete fairDice;
    return 0;
}
