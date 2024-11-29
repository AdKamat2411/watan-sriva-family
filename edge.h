#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <string>
#include <array>
#include <memory>
#include <iostream> // Required for ostream

class Edge {
    std::string owner;
    int Idx;
    std::array<std::shared_ptr<Vertex>, 2> vertices; // Use shared_ptr for proper memory management
public:
    Edge(int Idx, std::array<std::shared_ptr<Vertex>, 2> vertices = {nullptr, nullptr}, std::string owner = "");
    bool isAvailable() const;
    void setOwner(const std::string& s);
    std::string getName() const;
    int getIdx() const;
    void setVertices(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);
    std::array<std::shared_ptr<Vertex>, 2> getVertices() const;
    std::shared_ptr<Vertex> getConnectedVertex(int index) const;
};

// Overload for output operator
std::ostream& operator<<(std::ostream& out, const Edge& e);

#endif
