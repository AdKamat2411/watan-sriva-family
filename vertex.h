#include <string>

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
        void setOwner(string s);
};

ostream& operator<<(ostream& out, Vertex v);

