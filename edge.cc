#include "edge.h"
#include <iomanip>
#include <iostream>

Edge::Edge(int Idx, std::array<std::shared_ptr<Vertex>, 2> vertices, std::string owner)
    : Idx(Idx), owner(owner), vertices(vertices) {}

void Edge::setOwner(const std::string& s) {
    owner = s;
}

void Edge::setVertices(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2) {
    vertices[0] = v1;
    vertices[1] = v2;
}

std::array<std::shared_ptr<Vertex>, 2> Edge::getVertices() const {
    return vertices;
}

std::shared_ptr<Vertex> Edge::getConnectedVertex(int index) const {
    if (index < 0 || index >= 2) {
        return nullptr; 
    }
    return vertices[index];
}

int Edge::getIdx() const { 
    return Idx; 
}

std::string Edge::getName() const { 
    return owner; 
}

std::ostream& operator<<(std::ostream& out, const Edge& e) {
    if (e.getName().empty()) {
        out << std::setw(2) << std::right << e.getIdx();
    } else {
        if (e.getName() == "Blue") {
            out << "B";
        } else if (e.getName() == "Orange") {
            out << "O";
        } else if (e.getName() == "Red") {
            out << "R";
        } else {
            out << "Y";
        }
        out << 'A';
    }
    return out;
}

bool Edge::isAvailable() const{
    return owner.empty();
}
