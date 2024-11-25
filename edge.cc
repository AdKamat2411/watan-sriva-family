#include "edge.h"

Edge::Edge(int Idx, Vertex** vertArr, string owner): Idx{Idx}, owner{owner} {
    if (vertArr) {
        arr[0] = vertArr[0];
        arr[1] = vertArr[1];
    }
}

void Edge::setOwner(string s) {
    owner = s;
}
