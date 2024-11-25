#include "vertex.h"

Vertex::Vertex(int Idx, std::string owner = "", int houseLevel = 0) : Idx{Idx}, 
    owner{owner}, houseLevel{houseLevel} {}

void Vertex::upgradeCriterion() { houseLevel++; }

void Vertex::setOwner(string s) {
    owner = s;
}
