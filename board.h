#ifndef BOARD_H
#define BOARD_H

#include "vertex.h"
#include "edge.h"
#include "tile.h"
#include "subject.h"
#include "observer.h"
#include "dice.h"
#include "player.h"
#include <memory>

class BoardSetup;

class Board: public Subject, public Observer, public std::enable_shared_from_this<Board>{
    std::array<std::shared_ptr<Vertex>, 54> vertices;  // Use shared_ptr
    std::array<std::shared_ptr<Edge>, 72> edges;       // Use shared_ptr
    std::array<std::unique_ptr<Tile>, 19> tiles;       // Tiles can remain unique_ptr
    std::shared_ptr<Dice> dice;                        // Dice as shared_ptr
    int currGeese;
    public:
        static const int vertArr[19][6];
        static const int edgeArr[19][6];

        Board(std::shared_ptr<Dice> dice, int currGeese = -1);
        void printBoard();
        void notifyTiles(int rollSum, std::vector<Player*>& players, int currTurn);
        void initializeBoard(BoardSetup& setupStrategy);
        Tile* getTile(int index) const;
        ~Board() noexcept = default;
        std::vector<int> getVerticesConnectedToEdge(int edge);
        Vertex* getVertex(int index) const;
        std::array<std::shared_ptr<Vertex>, 54>& getVertices(); 
        std::array<std::shared_ptr<Edge>, 72>& getEdges();
        std::array<std::unique_ptr<Tile>, 19>& getTiles();
        void notify(int rollSum, std::vector<Player*>& players, int currTurn) override;
        void loadState(const std::vector<std::pair<std::string, int>>& tilesData);
};

#endif
