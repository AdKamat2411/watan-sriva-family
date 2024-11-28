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
        int idx;
        string color;               // Color of the player
        int victoryPoints;          // Total victory points
        static const int NUM_RESOURCES = 5; // Fixed number of resources
        Resource resources[NUM_RESOURCES] = { // Predefined resources with initial counts of 0
            {"CAFFEINE", 2},
            {"LAB", 2},
            {"LECTURE", 2},
            {"STUDY", 0},
            {"TUTORIAL", 2}
        };
        std::vector<int> goals;
        std::vector<std::pair<int, int>> criteria;
        int findResource(const string& resourceName) const;

    public:
        Player(const string& color, int idx);
        string getColor() const;
        int getVictoryPoints() const;
        void addResources(const string& resourceName, int amount);
        bool removeResources(const string& resourceName, int amount);
        int getResourceCount(const string& resourceName) const;
        static bool trade(Player& requester, Player& accepter, const string& resource1, const string& resource2);
        bool buildCriterion(Vertex& targetVertex, Edge* connectedEdges[], int numEdges);
        bool upgradeCriterion(Vertex& targetVertex);
        void addVictoryPoints(int points);
        void printStatus() const;
        void printCompletions(Vertex* allVertices[], int numVertices) const;
        bool claimEdge(Edge& targetEdge, Edge* allEdges[], int numEdges);
        std::vector<int> getGoals();
        std::vector<std::pair<int, int>> getCriteria();
};

#endif // PLAYER_H

