#include "vertex.h"
#include <iomanip>

Vertex::Vertex(int Idx, std::string owner = "", int houseLevel = 0) : Idx{Idx}, 
    owner{owner}, houseLevel{houseLevel} {}

void Vertex::upgradeCriterion() { houseLevel++; }

void Vertex::setOwner(string s) {
    owner = s;
}

int Vertex::getIdx() { return Idx; }

string Vertex::getName() { return owner; }

ostream& operator<<(ostream& out, Vertex v) {
    if (v.getName() == "") {
        out << std::setw(2) << v.getIdx();
    } else {
        out << v.getName();
    }
    return out;
}

