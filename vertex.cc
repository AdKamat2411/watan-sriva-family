#include "vertex.h"
#include <iomanip>

Vertex::Vertex(int Idx, string owner, string houseLevel)
    : Idx(Idx), owner(owner), houseLevel(houseLevel) {}

void Vertex::setOwner(string s) {
    owner = s;
}

void Vertex::setHouseLevel(const string& level) {
    houseLevel = level;
}

string Vertex::getHouseLevel() const {
    return houseLevel;
}

int Vertex::getIdx() const {
    return Idx;
}

string Vertex::getName() const {
    return owner;
}

bool Vertex::isAvailabale() const {
    return owner.empty();
}

ostream& operator<<(ostream& out, const Vertex& v) {
    if (v.getName().empty()) {
        out << std::setw(2) << std::right << v.getIdx();
    } else {
        out << v.getName() << " (" << v.getHouseLevel() << ")";
    }
    return out;
}

