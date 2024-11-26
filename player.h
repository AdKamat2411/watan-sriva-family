#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "vertex.h"
#include "edge.h"

using namespace std;

class Player {
private:
    struct Resource {
        string name;  // Name of the resource
        int count;    // Count of the resource
    };

    string color;               // Color of the player
    int victoryPoints;          // Total victory points
    static const int NUM_RESOURCES = 5; // Fixed number of resources
    Resource resources[NUM_RESOURCES] = { // Predefined resources with initial counts of 0
        {"CAFFEINE", 0},
        {"LAB", 0},
        {"LECTURE", 0},
        {"STUDY", 0},
        {"TUTORIAL", 0}
    };

    // Helper to find a resource index by name
    int findResource(const string& resourceName) const;

public:
    Player(const string& color);

    // Accessors
    string getColor() const;
    int getVictoryPoints() const;

    // Resource management
    void addResources(const string& resourceName, int amount);
    bool removeResources(const string& resourceName, int amount);
    int getResourceCount(const string& resourceName) const;

    // Build actions
    bool buildCriterion(Vertex& targetVertex, Edge* connectedEdges[], int numEdges);

    // Victory point management
    void addVictoryPoints(int points);
};

#endif // PLAYER_H

