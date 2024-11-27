#ifndef EDGE_H
#define EDGE_H

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
        string getName() const;
        int getIdx() const;
        void setVertices(Vertex* v1, Vertex* v2);
        Vertex** getVertices();
};

ostream& operator<<(ostream& out,const Edge &e);

#endif
