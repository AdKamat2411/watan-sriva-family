#include "player.h"

// Constructor
Player::Player(const string& color)
    : color(color), victoryPoints(0) {}


int Player::findResource(const string& resourceName) const {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (resources[i].name == resourceName) {
            return i;
        }
    }
    return -1; // Resource not found
}

string Player::getColor() const {
    return color;
}

int Player::getVictoryPoints() const {
    return victoryPoints;
}

void Player::addResources(const string& resourceName, int amount) {
    int index = findResource(resourceName);
    if (index != -1 && amount > 0) {
        resources[index].count += amount;
    } else {
        cerr << "Invalid resource name or amount." << endl;
    }
}

bool Player::removeResources(const string& resourceName, int amount) {
    int index = findResource(resourceName);
    if (index != -1 && amount > 0) {
        if (resources[index].count >= amount) {
            resources[index].count -= amount;
            return true;
        } else {
            cerr << "Insufficient resources of type: " << resourceName << endl;
        }
    } else {
        cerr << "Invalid resource name or amount." << endl;
    }
    return false;
}

int Player::getResourceCount(const string& resourceName) const {
    int index = findResource(resourceName);
    return (index != -1) ? resources[index].count : 0;
}

bool Player::buildCriterion(Vertex& targetVertex, Edge* connectedEdges[], int numEdges) {
    const int CAFFEINE_REQUIRED = 1;
    const int LAB_REQUIRED = 1;
    const int LECTURE_REQUIRED = 1;
    const int TUTORIAL_REQUIRED = 1;

    if (!targetVertex.isAvailabale()) {
        cerr << "Vertex " << targetVertex.getIdx() << " is not available for building." << endl;
        return false;
    }

    for (int i = 0; i < numEdges; ++i) {
        Edge* edge = connectedEdges[i];
        if (edge) {
            for (int j = 0; j < 2; ++j) { // Iterate through the two vertices connected by the edge
                Vertex* connectedVertex = edge->arr[j];
                if (connectedVertex && connectedVertex != &targetVertex) { // Skip the target vertex
                    if (connectedVertex->getName() != "") { // Check if this vertex is already owned
                        cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                             << " as a connected vertex ("
                             << connectedVertex->getIdx() << ") already has a criterion." << endl;
                        return false;
                    }
                }
            }
        }
    }

    if (getResourceCount("CAFFEINE") < CAFFEINE_REQUIRED ||
        getResourceCount("LAB") < LAB_REQUIRED ||
        getResourceCount("LECTURE") < LECTURE_REQUIRED ||
        getResourceCount("TUTORIAL") < TUTORIAL_REQUIRED) {
        cerr << "Not enough resources to build a criterion. Requires "
             << CAFFEINE_REQUIRED << " CAFFEINE, " << LAB_REQUIRED << " LAB, "
             << LECTURE_REQUIRED << " LECTURE, and " << TUTORIAL_REQUIRED << "." << endl;
        return false;
    }

    removeResources("CAFFEINE", CAFFEINE_REQUIRED);
    removeResources("LAB", LAB_REQUIRED);
    removeResources("LECTURE", LECTURE_REQUIRED);
    removeResources("TUTORIAL", TUTORIAL_REQUIRED);
    targetVertex.setOwner(color);
    targetVertex.upgradeCriterion();
    addVictoryPoints(1);

    cout << color << " player successfully built a criterion on Vertex "
         << targetVertex.getIdx() << "." << endl;

    return true;
}

void Player::addVictoryPoints(int points) {
    if (points > 0) {
        victoryPoints += points;
    } else {
        cerr << "Cannot add negative or zero victory points." << endl;
    }
}
