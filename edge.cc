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

int Edge::getIdx() const { return Idx; }

string Edge::getName() const { return owner; }

ostream& operator<<(ostream& out, const Edge &e) {
    if (e.getName() == "") {
        out << std::setw(2) << std::right << e.getIdx();
    } else {
        out << e.getName();
    }
    return out;
}
