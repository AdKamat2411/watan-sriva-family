#include "edge.h"
#include <iomanip>

Edge::Edge(int Idx, Vertex** vertArr, string owner): Idx{Idx}, owner{owner} {
    if (vertArr) {
        arr[0] = vertArr[0];
        arr[1] = vertArr[1];
    }
}

void Edge::setOwner(string s) {
    owner = s;
}

int Vertex::getIdx() { return Idx; }

string Vertex::getName() { return owner; }

ostream& operator<<(ostream& out, Edge e) {
    if (e.getName() == "") {
        out << std::setw(2) << e.getIdx();
    } else {
        out << e.getName();
    }
    return out;
}