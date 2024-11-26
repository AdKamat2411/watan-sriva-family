#include "board.h"
#include <iostream>
#include <iomanip>

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

Board::Board(int currGeese): currGeese(currGeese) {
    for (int i = 0; i < 54; i++) {
        vertices[i] = new Vertex(i);
    }

    for (int i = 0; i < 72; i++) {
        edges[i] = new Edge(i);
    }

    for (int i = 0; i < 19; i++) {
        Vertex* tempVertices[6];
        Edge* tempEdges[6];
        for (int j = 0; j < 6; j++) {
            tempVertices[j] = vertices[vertArr[i][j]];
            tempEdges[j] = edges[edgeArr[i][j]];
        }

        if (i != 0) {
            tiles[i] = new Tile(tempVertices, tempEdges);
        } else {
            tiles[i] = new Tile(tempVertices, tempEdges, "CAFFIENE");
        }
        
    }
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

void Board::printBoard() {
    for (int i = 0; i < 41; i++) {
        if (i == 0) {
            printSpaces(33);
            printSide(*vertices[0], *edges[0], *vertices[1]);
            printSpaces(37);
            cout << '\n';
        }

        if (i == 40) {
            printSpaces(33);
            printSide(*vertices[52], *edges[71], *vertices[53]);
            printSpaces(37);
            cout << '\n';
        }

        if (i == 1) {
            printSpaces(33);
            cout << '/';
            printSpaces(12);
            cout << '\\';
            printSpaces(33);
            cout << '\n';
        }

        if (i == 39) {
            printSpaces(33);
            cout << '\\';
            printSpaces(12);
            cout << '/';
            printSpaces(33);
            cout << '\n';
        }

        if (i == 2) {
            printSpaces(31);
            cout << *edges[1];
            printSpaces(6);
            cout << " 0";
            printSpaces(5);
            cout << *edges[2];
            printSpaces(36);
            cout << '\n';
        }

        if (i == 38) {
            printSpaces(31);
            cout << *edges[69];
            printSpaces(14);
            cout << *edges[70];
            printSpaces(35);
            cout << '\n';
        }

        if (i == 3) {
            printSpaces(31);
            cout << '/';
            printSpaces(5);
            cout << setw(8) << left << tiles[0]->getResource();
            printSpaces(3);
            cout << '\\';
            cout << '\n';
        }

        if (i == 37) {
            printSpaces(31);
            cout << '\\';
            printSpaces(16);
            cout << '/';
            cout << '\n';
        }

        if (i == 4) {
            printSpaces(17);
            printSide(*vertices[2], *edges[3], *vertices[3]);
            printSpaces(18);
            printSide(*vertices[4], *edges[4], *vertices[5]);
            cout << '\n';
        }

        if (i == 36) {
            printSpaces(17);
            printSide(*vertices[48], *edges[67], *vertices[49]);
            printSpaces(18);
            printSide(*vertices[50], *edges[68], *vertices[51]);
            cout << '\n';
        }



        
    }
}

Board::~Board() {
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
