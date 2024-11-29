#ifndef TILE_H
#define TILE_H

#include "vertex.h"
#include "edge.h"
#include <string>
#include "observer.h"
#include "player.h"
#include <memory>
#include <array>

class Tile : public Observer {
    std::string resourceType;
    int dieValue;
    bool geeseFlag;
    std::array<std::shared_ptr<Vertex>, 6> adjacentVert; // Use shared_ptr for Vertex
    std::array<std::shared_ptr<Edge>, 6> adjacentEdge;   // Use shared_ptr for Edge

public:
    Tile(const std::array<std::shared_ptr<Vertex>, 6>& adjacentVert,
         const std::array<std::shared_ptr<Edge>, 6>& adjacentEdge,
         const std::string& resourceType = "", int dieValue = -1, bool geeseFlag = false);
    void distributeResources(std::vector<Player*>& players);
    void updateGeese();
    int getDieVal() const;
    std::string getResource() const;
    void setResource(const std::string& resource);
    void setDieVal(int value);
    void notify(int rollSum, std::vector<Player*>& players, int currTurn) override;
    const std::array<std::shared_ptr<Vertex>, 6>& getAdjacentVertices() const;
    bool isGeese() const;
};

#endif
