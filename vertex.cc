#include "vertex.h"
#include <iomanip>

Vertex::Vertex(int Idx, string owner, int houseLevel) : Idx(Idx), 
    owner(owner), houseLevel(houseLevel) {}

void Vertex::upgradeCriterion() { houseLevel++; }

void Vertex::setOwner(string s) {
    owner = s;
}

int Vertex::getIdx() const { return Idx; }

bool Vertex::isAvailable() {
    if (owner == "") {
        return false;
    } else {
        return true;
    }
}

string Vertex::getName() const { return owner; }

ostream& operator<<(ostream& out, const Vertex &v) {
    if (v.getName() == "") {
        out << std::setw(2) << std::right << v.getIdx();
    } else {
        out << v.getName();
    }
    return out;
}

