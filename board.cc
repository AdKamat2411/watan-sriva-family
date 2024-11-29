#include "board.h"
#include <iostream>
#include "observer.h"
#include <iomanip>
#include "boardsetup.h"
#include <vector>

const int Board::vertArr[19][6] = {
    {0, 1, 4, 9, 8, 3},
    {2, 3, 8, 14, 13, 7},
    {4, 5, 10, 16, 15, 9},
    {6, 7, 13, 19, 18, 12},
    {8, 9, 15, 21, 20, 14},
    {10, 11, 17, 23, 22, 16},
    {13, 14, 20, 26, 25, 19},
    {15, 16, 22, 28, 27, 21},
    {18, 19, 25, 31, 30, 24},
    {20, 21, 27, 33, 32, 26},
    {22, 23, 29, 35, 34, 28},
    {25, 26, 32, 38, 37, 31},
    {27, 28, 34, 40, 39, 33},
    {30, 31, 37, 43, 42, 36},
    {32, 33, 39, 45, 44, 38},
    {34, 35, 41, 47, 46, 40},
    {37, 38, 44, 49, 48, 43},
    {39, 40, 46, 51, 50, 45},
    {44, 45, 50, 53, 52, 49}
};

const int Board::edgeArr[19][6] = {
    {0, 2, 7, 10, 6, 1},
    {3, 6, 14, 18, 13, 5},
    {4, 8, 16, 19, 15, 7},
    {9, 13, 21, 26, 20, 12},
    {10, 15, 23, 27, 22, 14},
    {11, 17, 25, 28, 24, 16},
    {18, 22, 31, 35, 30, 21},
    {19, 24, 33, 36, 32, 23},
    {26, 30, 38, 43, 37, 29},
    {27, 32, 40, 44, 39, 31},
    {28, 34, 42, 45, 41, 33},
    {35, 39, 48, 52, 47, 38},
    {36, 41, 50, 53, 49, 40},
    {43, 47, 55, 60, 54, 46},
    {44, 49, 57, 61, 56, 48},
    {45, 51, 59, 62, 58, 50},
    {52, 56, 64, 67, 63, 55},
    {53, 58, 66, 68, 65, 57},
    {61, 65, 70, 71, 69, 64}
};

Board::Board(Dice* dice, int currGeese) : dice(dice), currGeese(currGeese) {
    dice->attach(this);
    for (int i = 0; i < 54; i++) {
        vertices[i] = new Vertex(i);
    }
    for (int i = 0; i < 72; i++) {
        edges[i] = new Edge(i);
        std::vector<int> connectedVert = getVerticesConnectedToEdge(i);
        edges[i]->setVertices(vertices[connectedVert[0]], vertices[connectedVert[1]]);
    }
    for (int i = 0; i < 19; i++) {
        Vertex* tempVertices[6];
        Edge* tempEdges[6];
        for (int j = 0; j < 6; j++) {
            tempVertices[j] = vertices[vertArr[i][j]];
            tempEdges[j] = edges[edgeArr[i][j]];
        }

        tiles[i] = new Tile(tempVertices, tempEdges);
        
    }
}
int boundary_edges[] = {0, 2, 4, 8, 11, 17, 25, 34, 42, 51, 59, 62, 66, 68, 70, 71, 69, 67, 63, 60, 54, 46, 37, 29, 20, 12, 9, 5, 3, 1};
int vertices_edges[][2] = {
    {0, 1},
    {1, 4},
    {4, 5},
    {5, 10},
    {10, 11},
    {11, 17},
    {17, 23},
    {23, 29},
    {29, 35},
    {35, 41},
    {41, 47},
    {46, 47},
    {46, 51},
    {51, 50},
    {50, 53},
    {53, 52},
    {52, 49},
    {49, 48},
    {48, 43},
    {43, 42},
    {42, 36},
    {36, 30},
    {30, 24},
    {24, 18},
    {18, 12},
    {12, 6},
    {6, 7},
    {7, 2},
    {2, 3},
    {3, 0}
};

std::vector<int> Board::getVerticesConnectedToEdge(int edge) {
    std::vector<int> result; // Dynamic vector to store connected vertices
    for (int k = 0; k < 30; ++k) {
        if (edge == boundary_edges[k]) {
            return {vertices_edges[k][0], vertices_edges[k][1]};
        }
    }
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 6; j++) {
            if (edgeArr[i][j] == edge) {
                int tileIndex1 = i;

                int tileIndex2 = -1;
                for (int k = 0; k < 19; k++) {
                    if (k != tileIndex1) {
                        for (int l = 0; l < 6; l++) {
                            if (edgeArr[k][l] == edge) {
                                tileIndex2 = k;
                                break;
                            }
                        }
                    }
                }

                if (tileIndex2 != -1) {
                    for (int m = 0; m < 6; m++) {
                        for (int n = 0; n < 6; n++) {
                            if (vertArr[tileIndex1][m] == vertArr[tileIndex2][n]) {
                                result.push_back(vertArr[tileIndex1][m]);
                                if (result.size() == 2) return result; // Found both vertices
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

void printSpaces(int num) {
    for (int i = 0; i < num; i++) {
        cout << ' ';
    }
}

void printSide(Vertex v0, Edge e0, Vertex v1) {
    cout << '|' << v0 << "|--" << e0 << "--|" << v1 << '|';
}

// board size is 84x41 chars
// each tile side has 16 chars
// empty space in the centre of the tile is 16 chars

void printGeese(int tileNum, Tile** tiles) {
    if (tiles[tileNum]->isGeese()) {
        cout << "GEESE";
    } else {
        cout << "     ";
    }
}

ostream& printDie(ostream& out, Tile* tile) {
    if (tile->getResource() == "NETFLIX") {
        out << "  ";
    } else {
        out << setw(2) << right << tile->getDieVal();
    }
    return out;
}


void Board::printBoard() {
    for (int i = 0; i < 41; i++) {
        if (i == 0) {
            printSpaces(39);
            printSide(*vertices[0], *edges[0], *vertices[1]);
            printSpaces(37);
            cout << '\n';
        }

        if (i == 40) {
            printSpaces(39);
            printSide(*vertices[52], *edges[71], *vertices[53]);
            printSpaces(37);
            cout << '\n';
        }

        if (i == 1) {
            printSpaces(39);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(33);
            cout << '\n';
        }

        if (i == 39) {
            printSpaces(39);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(33);
            cout << '\n';
        }

        if (i == 2) {
            printSpaces(37);
            cout << *edges[1];
            printSpaces(6);
            cout << " 0";
            printSpaces(5);
            cout << *edges[2];
            printSpaces(36);
            cout << '\n';
        }

        if (i == 38) {
            printSpaces(37);
            cout << *edges[69];
            printSpaces(14);
            cout << *edges[70];
            printSpaces(35);
            cout << '\n';
        }

        if (i == 3) {
            printSpaces(37);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[0]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 37) {
            printSpaces(37);
            cout << '\\';
            printSpaces(5);
            printGeese(18, tiles);
            printSpaces(6);
            cout << '/';
            cout << '\n';
        }

        if (i == 4) {
            printSpaces(24);
            printSide(*vertices[2], *edges[3], *vertices[3]);
            printSpaces(7);
            printDie(cout, tiles[0]);
            printSpaces(7);
            printSide(*vertices[4], *edges[4], *vertices[5]);
            cout << '\n';
        }

        if (i == 36) {
            printSpaces(24);
            printSide(*vertices[48], *edges[67], *vertices[49]);
            printSpaces(7);
            printDie(cout, tiles[18]);
            printSpaces(7);
            printSide(*vertices[50], *edges[68], *vertices[51]);
            cout << '\n';
        }

        if (i == 5) {
            printSpaces(24);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(0, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            cout << '\n';
        }

        if (i == 35) {
            printSpaces(24);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[18]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            cout << '\n';
        }

        if (i == 6) {
            printSpaces(22);
            cout << *edges[5];
            printSpaces(6);
            cout << " 1";
            printSpaces(5);
            cout << *edges[6];
            printSpaces(13);
            cout << *edges[7];
            printSpaces(6);
            cout << " 2";
            printSpaces(5);
            cout << *edges[8];
            cout << '\n';
        }

        if (i == 34) {
            printSpaces(22);
            cout << *edges[63];
            printSpaces(13);;
            cout << *edges[64];
            printSpaces(6);
            cout << "18";
            printSpaces(5);
            cout << *edges[65];
            printSpaces(13);
            cout << *edges[66];
            cout << '\n';
        }

        if (i == 7) {
            printSpaces(22);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[1]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[2]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 33) {
            printSpaces(22);
            cout << '\\';
            printSpaces(5);
            printGeese(16, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(17, tiles);
            printSpaces(6);
            cout << '/';
            cout << '\n';
        }

        if (i == 8) {
            printSpaces(9);
            printSide(*vertices[6], *edges[9], *vertices[7]);
            printSpaces(7);
            printDie(cout, tiles[1]);
            printSpaces(7);
            printSide(*vertices[8], *edges[10], *vertices[9]);
            printSpaces(7);
            printDie(cout, tiles[2]);
            printSpaces(7);
            printSide(*vertices[10], *edges[11], *vertices[11]);
            cout << '\n';
        }

        if (i == 32) {
            printSpaces(9);
            printSide(*vertices[42], *edges[60], *vertices[43]);
            printSpaces(7);
            printDie(cout, tiles[16]);
            printSpaces(7);
            printSide(*vertices[44], *edges[61], *vertices[45]);
            printSpaces(7);
            printDie(cout, tiles[17]);
            printSpaces(7);
            printSide(*vertices[46], *edges[62], *vertices[47]);
            cout << '\n';
        }

        if (i == 9) {
            printSpaces(9);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(1, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(2, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            cout << '\n';
        }

        if (i == 31) {
            printSpaces(9);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[16]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[17]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            cout << '\n';
        }

        if (i == 10) {
            printSpaces(7);
            cout << *edges[12];
            printSpaces(6);
            cout << " 3";
            printSpaces(5);
            cout << *edges[13];
            printSpaces(13);
            cout << *edges[14];
            printSpaces(6);
            cout << " 4";
            printSpaces(5);
            cout << *edges[15];
            printSpaces(13);
            cout << *edges[16];
            printSpaces(6);
            cout << " 5";
            printSpaces(5);
            cout << *edges[17];
            cout << '\n';
        }

        if (i == 30) {
            printSpaces(7);
            cout << *edges[54];
            printSpaces(13);
            cout << *edges[55];
            printSpaces(6);
            cout << "16";
            printSpaces(5);
            cout << *edges[56];
            printSpaces(13);
            cout << *edges[57];
            printSpaces(6);
            cout << "17";
            printSpaces(5);
            cout << *edges[58];
            printSpaces(13);
            cout << *edges[59];
            cout << '\n';
        }

        if (i == 11) {
            printSpaces(7);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[3]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[4]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[5]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 29) {
            printSpaces(7);
            cout << '\\';
            printSpaces(5);
            printGeese(13, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(14, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(15, tiles);
            printSpaces(6);
            cout << '/';
            cout << '\n';
        }

        if (i == 12) {
            printSpaces(4);
            cout << '|';
            cout << *vertices[12];
            cout << '|';
            printSpaces(7);
            printDie(cout, tiles[3]);
            printSpaces(7);
            printSide(*vertices[13], *edges[18], *vertices[14]);
            printSpaces(7);
            printDie(cout, tiles[4]);
            printSpaces(7);
            printSide(*vertices[15], *edges[19], *vertices[16]);
            printSpaces(7);
            printDie(cout, tiles[5]);
            printSpaces(7);
            cout << '|';
            cout << *vertices[17];
            cout << '|';
            cout << '\n';
        }

        if (i == 28) {
            printSpaces(4);
            cout << '|';
            cout << *vertices[36];
            cout << '|';
            printSpaces(7);
            printDie(cout, tiles[13]);
            printSpaces(7);
            printSide(*vertices[37], *edges[52], *vertices[38]);
            printSpaces(7);
            printDie(cout, tiles[14]);
            printSpaces(7);
            printSide(*vertices[39], *edges[53], *vertices[40]);
            printSpaces(7);
            printDie(cout, tiles[15]);
            printSpaces(7);
            cout << '|';
            cout << *vertices[41];
            cout << '|';
            cout << '\n';
        }

        if (i == 13) {
            printSpaces(7);
            cout << '\\';
            printSpaces(5);
            printGeese(3, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(4, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(5, tiles);
            printSpaces(6);
            cout << '/';
            cout << '\n';
        }

        if (i == 27) {
            printSpaces(7);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[13]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[14]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[15]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 14) {
            printSpaces(7);
            cout << *edges[20];
            printSpaces(13);
            cout << *edges[21];
            printSpaces(6);
            cout << " 6";
            printSpaces(5);
            cout << *edges[22];
            printSpaces(13);
            cout << *edges[23];
            printSpaces(6);
            cout << " 7";
            printSpaces(5);
            cout << *edges[24];
            printSpaces(13);
            cout << *edges[25];
            cout << '\n';
        }

        if (i == 26) {
            printSpaces(7);
            cout << *edges[46];
            printSpaces(6);
            cout << "13";
            printSpaces(5);
            cout << *edges[47];
            printSpaces(13);
            cout << *edges[48];
            printSpaces(6);
            cout << "14";
            printSpaces(5);
            cout << *edges[49];
            printSpaces(13);
            cout << *edges[50];
            printSpaces(6);
            cout << "15";
            printSpaces(5);
            cout << *edges[51];
            cout << '\n';
        }

        if (i == 15) {
            printSpaces(9);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[6]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[7]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            cout << '\n';
        }

        if (i == 25) {
            printSpaces(9);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(11, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(12, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            cout << '\n';
        }

        if (i == 16) {
            printSpaces(9);
            printSide(*vertices[18], *edges[26], *vertices[19]);
            printSpaces(7);
            printDie(cout, tiles[6]);
            printSpaces(7);
            printSide(*vertices[20], *edges[27], *vertices[21]);
            printSpaces(7);
            printDie(cout, tiles[7]);
            printSpaces(7);
            printSide(*vertices[22], *edges[28], *vertices[23]);
            cout << '\n';
        }

        if (i == 24) {
            printSpaces(9);
            printSide(*vertices[30], *edges[43], *vertices[31]);
            printSpaces(7);
            printDie(cout, tiles[11]);
            printSpaces(7);
            printSide(*vertices[32], *edges[44], *vertices[33]);
            printSpaces(7);
            printDie(cout, tiles[12]);
            printSpaces(7);
            printSide(*vertices[34], *edges[45], *vertices[35]);
            cout << '\n';
        }

        if (i == 17) {
            printSpaces(9);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(6, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(7, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            cout << '\n';
        }

        if (i == 23) {
            printSpaces(9);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[11]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[12]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            cout << '\n';
        }

        if (i == 18) {
            printSpaces(7);
            cout << *edges[29];
            printSpaces(6);
            cout << " 8";
            printSpaces(5);
            cout << *edges[30];
            printSpaces(13);
            cout << *edges[31];
            printSpaces(6);
            cout << " 9";
            printSpaces(5);
            cout << *edges[32];
            printSpaces(13);
            cout << *edges[33];
            printSpaces(6);
            cout << "10";
            printSpaces(5);
            cout << *edges[34];
            cout << '\n';
        }

        if (i == 22) {
            printSpaces(7);
            cout << *edges[37];
            printSpaces(13);
            cout << *edges[38];
            printSpaces(6);
            cout << "11";
            printSpaces(5);
            cout << *edges[39];
            printSpaces(13);
            cout << *edges[40];
            printSpaces(6);
            cout << "12";
            printSpaces(5);
            cout << *edges[41];
            printSpaces(13);
            cout << *edges[42];
            cout << '\n';
        }

        if (i == 19) {
            printSpaces(7);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[8]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[9]->getResource();
            printSpaces(3);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[10]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 21) {
            printSpaces(7);
            cout << '\\';
            printSpaces(5);
            printGeese(8, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(9, tiles);
            printSpaces(6);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(5);
            printGeese(10, tiles);
            printSpaces(6);
            cout << '/';
            cout << '\n';
        }

        if (i == 20) {
            printSpaces(4);
            cout << '|';
            cout << *vertices[24];
            cout << '|';
            printSpaces(7);
            printDie(cout, tiles[8]);
            printSpaces(7);
            printSide(*vertices[25], *edges[35], *vertices[26]);
            printSpaces(7);
            printDie(cout, tiles[9]);
            printSpaces(7);
            printSide(*vertices[27], *edges[36], *vertices[28]);
            printSpaces(7);
            printDie(cout, tiles[10]);
            printSpaces(7);
            cout << '|';
            cout << *vertices[29];
            cout << '|';
            cout << '\n';
        }
    }
}

void Board::notify(int rollSum, std::vector<Player*>& players, int currTurn) {
    if (rollSum == -1) {
        rollSum = dice->getSumOfRoll();
    }
    notifyTiles(rollSum, players, currTurn);
}

void Board::notifyTiles(int rollSum, std::vector<Player*>& players, int currTurn) {
    for (int i = 0; i < 19; i++) {
        if (tiles[i]->getDieVal() == rollSum && !(tiles[i]->isGeese())) {
            tiles[i]->notify(rollSum, players, currTurn);
            players[currTurn]->addResources(tiles[i]->getResource(), 1);
        }
    }
}

Board::~Board() {
    dice->detach(this);
    for (int i = 0; i < 54; i++) {
        delete vertices[i];
    }

    for (int i = 0; i < 71; i++) {
        delete edges[i];
    }

    // for (int i = 0; i < 19; i++) {
    //     delete tiles[i];
    // }
}

void Board::initializeBoard(BoardSetup& setupStrategy) {
    setupStrategy.setup(*this);
}

Tile* Board::getTile(int index) const {
    return tiles[index];
}

Vertex* Board::getVertex(int index) const {
    for (int i = 0; i < 54; ++i) {
        if (vertices[i]->getIdx() == index) {
            return vertices[i];
        }
    }
}

Vertex** Board::getVertices() {
    return vertices;
}

Edge** Board::getEdges() {
    return edges;
}

Tile** Board::getTiles() { return tiles; }

void Board::loadState(const std::vector<std::pair<std::string, int>>& tilesData) {
    for (int i = 0; i < 19; ++i) {
        if (tiles[i] == nullptr) {
            Vertex* tempVertices[6]; 
            Edge* tempEdges[6]; 
            for (int j = 0; j < 6; ++j) {
                tempVertices[j] = vertices[vertArr[i][j]];
                tempEdges[j] = edges[edgeArr[i][j]];
            }    
            tiles[i] = new Tile(tempVertices, tempEdges);
        }
        tiles[i]->setResource(tilesData[i].first);
        tiles[i]->setDieVal(tilesData[i].second);
    }
}
