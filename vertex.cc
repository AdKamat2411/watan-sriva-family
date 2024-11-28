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

bool Vertex::isAvailable() const {
    return owner.empty();
}

ostream& operator<<(ostream& out, const Vertex &v) {
    if (v.getName() == "") {
        out << std::setw(2) << std::right << v.getIdx();
    } else {
        if (v.getName() == "Blue") {
            out << "B";
        } else if (v.getName() == "Orange") {
            out << "O";
        } else if (v.getName() == "Red") {
            out << "R";
        } else {
            out << "Y";
        }
        if (v.getHouseLevel() == "Assignment") {
            out << "A";
        } else if (v.getHouseLevel() == "Midterm") {
            out << "M";
        } else {
            out << "E";
        }
    }
    return out;
}
