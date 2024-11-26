#include "board.h"
using namespace std;

int main() {
    Dice* fairDice = new FairDice();
    Board board(fairDice);
    cout << "Initial Board State:" << endl;
    board.printBoard();
    cout << "\nRolling the dice:" << endl;
    fairDice->roll();
    delete fairDice;
    return 0;
}
