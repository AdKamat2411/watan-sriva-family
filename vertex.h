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
        string getName();
        int getIdx();
        void setOwner(string s);
};

export ostream& operator<<(ostream& out, Vertex v);

