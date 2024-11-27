#include "edge.h"
#include <iomanip>

Edge::Edge(int Idx, Vertex** vertArr, string owner): Idx(Idx), owner(owner) {
    arr[0] = arr[1] = nullptr;
    if (vertArr) {
        arr[0] = vertArr[0];
        arr[1] = vertArr[1];
    }
}

void Edge::setOwner(string s) {
    owner = s;
}

void Edge::setVertices(Vertex* v1, Vertex* v2) {
    arr[0] = v1;
    arr[1] = v2;
}

Vertex** Edge::getVertices() {
    return arr;
}

int Edge::getIdx() const { return Idx; }

string Edge::getName() const { return owner; }

ostream& operator<<(ostream& out, const Edge &e) {
    if (e.getName() == "") {
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
        out << e.getName() << 'A';
    }
    return out;
}

Vertex* Edge::getConnectedVertex(int index) const {
    if (index < 0 || index >= 2) {
        return nullptr; 
    }
    return arr[index];
}

bool Edge::isAvailabale() {
    return (owner == "");
}
