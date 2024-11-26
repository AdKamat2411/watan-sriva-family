#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <iostream>

using namespace std;

class Vertex {
    std::string owner;
    int houseLevel;
    int Idx;
    public:
        Vertex(int Idx, std::string owner = "", int houseLevel = 0);
        void upgradeCriterion();
        bool isAvailabale();
        string getName() const;
        int getIdx() const;
        void setOwner(string s);
};

ostream& operator<<(ostream& out, const Vertex &v);


#endif
