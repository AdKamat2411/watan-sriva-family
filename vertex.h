#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Vertex {
    string owner;
    string houseLevel; // "Assignment", "Midterm", "Exam"
    int Idx;

public:
    Vertex(int Idx, std::string owner = "", string houseLevel = "");
    bool isAvailable() const;
    string getName() const;
    int getIdx() const;
    string getHouseLevel() const; // Accessor for houseLevel
    void setOwner(string s);
    void setHouseLevel(const string& level); // Mutator for houseLevel
    
};


ostream& operator<<(ostream& out, const Vertex& v);

#endif
