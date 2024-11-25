#include "vertex.h"
#include <string>

class Edge {
    string owner;
    int Idx;
    Vertex* arr[2];
    public:
        Edge(int Idx, Vertex** arr = nullptr, string owner="");
        bool isAvailabale();
        void setOwner(string s);
};

ostream& operator<<(ostream& out, Edge v);
