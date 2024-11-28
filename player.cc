#include "player.h"

// Constructor
Player::Player(const string &color, int idx)
    : color(color), victoryPoints(0), idx(idx) {}

int Player::findResource(const string &resourceName) const
{
    for (int i = 0; i < NUM_RESOURCES; ++i)
    {
        if (resources[i].name == resourceName)
        {
            return i;
        }
    }
    return -1; // Resource not found
}

string Player::getColor() const
{
    return color;
}

int Player::getVictoryPoints() const
{
    return victoryPoints;
}

void Player::addResources(const string &resourceName, int amount)
{
    int index = findResource(resourceName);
    if (index != -1 && amount > 0)
    {
        resources[index].count += amount;
        cout << "Student " << color << " gained:" << endl;
        cout << amount << " " << resourceName << endl;
    }
    else
    {
        cerr << "Invalid resource name or amount." << endl;
    }
}

bool Player::removeResources(const string &resourceName, int amount)
{
    int index = findResource(resourceName);
    if (index != -1 && amount > 0)
    {
        if (resources[index].count >= amount)
        {
            resources[index].count -= amount;
            return true;
        }
        else
        {
            cerr << "Insufficient resources of type: " << resourceName << endl;
        }
    }
    else
    {
        cerr << "Invalid resource name or amount." << endl;
    }
    return false;
}

int Player::getResourceCount(const string &resourceName) const
{
    int index = findResource(resourceName);
    return (index != -1) ? resources[index].count : 0;
}

bool Player::trade(Player &requester, Player &accepter, const string &resource1, const string &resource2)
{
    int requesterIndex = requester.findResource(resource1);
    int accepterIndex = accepter.findResource(resource2);

    if (requesterIndex == -1 || accepterIndex == -1)
    {
        cerr << "Invalid resource name(s) for trade." << endl;
        return false;
    }

    if (requester.resources[requesterIndex].count < 1)
    {
        cerr << requester.getColor() << " player does not have enough " << resource1 << " to trade." << endl;
        return false;
    }

    if (accepter.resources[accepterIndex].count < 1)
    {
        cerr << accepter.getColor() << " player does not have enough " << resource2 << " to trade." << endl;
        return false;
    }

    // Execute trade
    requester.resources[requesterIndex].count -= 1;
    accepter.resources[accepterIndex].count -= 1;

    requester.resources[accepterIndex].count += 1;
    accepter.resources[requesterIndex].count += 1;

    cout << requester.getColor() << " player traded " << resource1
         << " with " << accepter.getColor() << " player for " << resource2 << "." << endl;

    return true;
}

bool Player::buildCriterion(Vertex &targetVertex, Edge *connectedEdges[], int numEdges)
{
    const int CAFFEINE_REQUIRED = 1;
    const int LAB_REQUIRED = 1;
    const int LECTURE_REQUIRED = 1;
    const int TUTORIAL_REQUIRED = 1;

    // Check if the target vertex is available
    if (!targetVertex.isAvailable())
    {
        cerr << "Vertex " << targetVertex.getIdx() << " is not available for building." << endl;
        return false;
    }

    // Check connected vertices for existing criteria using edges
    for (int i = 0; i < numEdges; ++i)
    {
        Edge *edge = connectedEdges[i];
        if (edge)
        {
            Vertex **vertArr = edge->getVertices();
            Vertex *Vertex1 = vertArr[0];
            Vertex *Vertex2 = vertArr[1];
            if (Vertex1 == &targetVertex)
            {
                if (Vertex2->getName() != "")
                {
                    cerr << "Cannot build on Vertex" << targetVertex.getIdx()
                         << "it's connected to vertex" << Vertex2->getIdx() << endl;
                    return false;
                }
            }
            else if (Vertex2 == &targetVertex)
            {
                if (Vertex1->getName() != "")
                {
                    cerr << "Cannot build on Vertex" << targetVertex.getIdx()
                         << "it's connected to vertex" << Vertex1->getIdx() << endl;
                    return false;
                }
            }
        }
    }

    // Check resource availability
    if (getResourceCount("CAFFEINE") < CAFFEINE_REQUIRED ||
        getResourceCount("LAB") < LAB_REQUIRED ||
        getResourceCount("LECTURE") < LECTURE_REQUIRED ||
        getResourceCount("TUTORIAL") < TUTORIAL_REQUIRED)
    {
        cerr << "Not enough resources to build a criterion. Requires "
             << CAFFEINE_REQUIRED << " CAFFEINE, " << LAB_REQUIRED << " LAB, "
             << LECTURE_REQUIRED << " LECTURE, and " << TUTORIAL_REQUIRED << " TUTORIAL." << endl;
        return false;
    }

    // Deduct resources
    removeResources("CAFFEINE", CAFFEINE_REQUIRED);
    removeResources("LAB", LAB_REQUIRED);
    removeResources("LECTURE", LECTURE_REQUIRED);
    removeResources("TUTORIAL", TUTORIAL_REQUIRED);

    // Build the criterion: Set ownership and house level
    targetVertex.setOwner(color);             // Assign ownership to the player
    targetVertex.setHouseLevel("Assignment"); // Set house level to Assignment
    addVictoryPoints(1);                      // Add victory point

    cout << color << " player successfully built a criterion (Assignment) on Vertex "
         << targetVertex.getIdx() << "." << endl;

    return true;
}

bool Player::buildCriterion2(Vertex &targetVertex, Edge *connectedEdges[], int numEdges) {
    const int CAFFEINE_REQUIRED = 1;
    const int LAB_REQUIRED = 1;
    const int LECTURE_REQUIRED = 1;
    const int TUTORIAL_REQUIRED = 1;

    // Check if the target vertex is available
    if (!targetVertex.isAvailable()) {
        cerr << "Vertex " << targetVertex.getIdx() << " is not available for building." << endl;
        return false;
    }

    // Check if the player owns at least one adjacent edge connected to the target vertex
    bool ownsAdjacentEdge = false;
    for (int i = 0; i < numEdges; ++i) {
        Edge *edge = connectedEdges[i];
        Vertex** arr = edge->getVertices();
        if (edge && (arr[0] == &targetVertex || arr[1] == &targetVertex)) {
            if (edge->getName() == color) { // Check if the edge is owned by the current player
                ownsAdjacentEdge = true;
                break;
            }
        }
    }

    if (!ownsAdjacentEdge) {
        cerr << "Cannot build on Vertex " << targetVertex.getIdx()
             << ". You must own an adjacent edge connected to it." << endl;
        return false;
    }

    // Check if all adjacent vertices are unowned
    for (int i = 0; i < numEdges; ++i) {
        Edge *edge = connectedEdges[i];
        if (edge) {
            Vertex **vertArr = edge->getVertices();
            Vertex *vertex1 = vertArr[0];
            Vertex *vertex2 = vertArr[1];

            if (vertex1 == &targetVertex && vertex2->getName() != "") { // Check adjacent vertex
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << ". Adjacent vertex (" << vertex2->getIdx() << ") is already owned." << endl;
                return false;
            }
            if (vertex2 == &targetVertex && vertex1->getName() != "") { // Check adjacent vertex
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << ". Adjacent vertex (" << vertex1->getIdx() << ") is already owned." << endl;
                return false;
            }
        }
    }

    // Check resource availability
    if (getResourceCount("CAFFEINE") < CAFFEINE_REQUIRED ||
        getResourceCount("LAB") < LAB_REQUIRED ||
        getResourceCount("LECTURE") < LECTURE_REQUIRED ||
        getResourceCount("TUTORIAL") < TUTORIAL_REQUIRED) {
        cerr << "Not enough resources to build a criterion. Requires "
             << CAFFEINE_REQUIRED << " CAFFEINE, " << LAB_REQUIRED << " LAB, "
             << LECTURE_REQUIRED << " LECTURE, and " << TUTORIAL_REQUIRED << " TUTORIAL." << endl;
        return false;
    }

    // Deduct resources
    removeResources("CAFFEINE", CAFFEINE_REQUIRED);
    removeResources("LAB", LAB_REQUIRED);
    removeResources("LECTURE", LECTURE_REQUIRED);
    removeResources("TUTORIAL", TUTORIAL_REQUIRED);

    // Build the criterion: Set ownership and house level
    targetVertex.setOwner(color);             // Assign ownership to the player
    targetVertex.setHouseLevel("Assignment"); // Set house level to Assignment
    addVictoryPoints(1);                      // Add victory point

    criteria.push_back(std::make_pair(targetVertex.getIdx(), 1));

    cout << color << " player successfully built a criterion (Assignment) on Vertex "
         << targetVertex.getIdx() << "." << endl;

    return true;
}

bool Player::upgradeCriterion(Vertex &targetVertex)
{
    if (targetVertex.getName() != color)
    {
        cerr << "You do not own this criterion!" << endl;
        return false;
    }
    string currentLevel = targetVertex.getHouseLevel();
    if (currentLevel == "Assignment")
    {
        // Upgrade to Midterm
        const int LECTURE_REQUIRED = 2;
        const int STUDY_REQUIRED = 3;
        if (getResourceCount("LECTURE") < LECTURE_REQUIRED ||
            getResourceCount("STUDY") < STUDY_REQUIRED)
        {
            cerr << "Not enough resources to upgrade to Midterm." << endl;
            return false;
        }
        removeResources("LECTURE", LECTURE_REQUIRED);
        removeResources("STUDY", STUDY_REQUIRED);
        targetVertex.setHouseLevel("Midterm");
        addVictoryPoints(1); // Add victory point
        cout << color << " player upgraded criterion to Midterm on Vertex "
             << targetVertex.getIdx() << "." << endl;
    }
    else if (currentLevel == "Midterm")
    {
        // Upgrade to Exam
        const int CAFFEINE_REQUIRED = 3;
        const int LAB_REQUIRED = 2;
        const int LECTURE_REQUIRED = 2;
        const int TUTORIAL_REQUIRED = 1;
        const int STUDY_REQUIRED = 2;
        if (getResourceCount("CAFFEINE") < CAFFEINE_REQUIRED ||
            getResourceCount("LAB") < LAB_REQUIRED ||
            getResourceCount("LECTURE") < LECTURE_REQUIRED ||
            getResourceCount("TUTORIAL") < TUTORIAL_REQUIRED ||
            getResourceCount("STUDY") < STUDY_REQUIRED)
        {
            cerr << "Not enough resources to upgrade to Exam." << endl;
            return false;
        }
        removeResources("CAFFEINE", CAFFEINE_REQUIRED);
        removeResources("LAB", LAB_REQUIRED);
        removeResources("LECTURE", LECTURE_REQUIRED);
        removeResources("TUTORIAL", TUTORIAL_REQUIRED);
        removeResources("STUDY", STUDY_REQUIRED);
        targetVertex.setHouseLevel("Exam");
        addVictoryPoints(1); // Add victory point
        cout << color << " player upgraded criterion to Exam on Vertex "
             << targetVertex.getIdx() << "." << endl;
    }
    else
    {
        cerr << "Criterion is already at the maximum level (Exam)." << endl;
        return false;
    }

    for (auto &criterion : criteria)
    {
        if (criterion.first == targetVertex.getIdx())
        {
            if (currentLevel == "Assignment")
            {
                criterion.second = 2; // Upgrade to Midterm
            }
            else if (currentLevel == "Midterm")
            {
                criterion.second = 3; // Upgrade to Exam
            }
            break;
        }
    }

    return true;
}

bool Player::claimEdge(Edge &targetEdge, Edge *allEdges[], int numEdges)
{
    const int TUTORIAL_COST = 1;
    const int STUDY_COST = 1;

    // Check if the edge is available
    if (!targetEdge.isAvailabale())
    {
        cerr << "Edge " << targetEdge.getIdx() << " is already owned by another player." << endl;
        return false;
    }

    // Check resource availability
    if (getResourceCount("TUTORIAL") < TUTORIAL_COST || getResourceCount("STUDY") < STUDY_COST)
    {
        cerr << "You do not have enough resources." << endl;
        return false;
    }

    // Check ownership of a connecting vertex or adjacent edge
    bool canClaim = false;
    for (int i = 0; i < 2; ++i)
    { // Loop through the two vertices connected by the edge
        Vertex **vertArr = targetEdge.getVertices();
        Vertex *vertex = vertArr[i];
        if (vertex && vertex->getName() == color)
        {
            // Player owns a criterion on this vertex
            canClaim = true;
            break;
        }

        // Check for adjacent edges sharing this vertex
        for (int j = 0; j < numEdges; ++j)
        {
            Edge *adjacentEdge = allEdges[j];
            if (adjacentEdge != &targetEdge)
            { // Skip the current edge
                if (adjacentEdge->getVertices()[0] == vertex || adjacentEdge->getVertices()[1] == vertex)
                {
                    if (adjacentEdge->getName() == color)
                    {
                        // Player owns an adjacent edge
                        canClaim = true;
                        break;
                    }
                }
            }
        }

        if (canClaim)
        {
            break; // No need to check further if the edge can already be claimed
        }
    }

    if (!canClaim)
    {
        cerr << "Cannot claim Edge " << targetEdge.getIdx()
             << ". You must own a connected criterion or an adjacent edge." << endl;
        return false;
    }

    // Deduct resources
    removeResources("TUTORIAL", TUTORIAL_COST);
    removeResources("STUDY", STUDY_COST);

    // Claim the edge
    targetEdge.setOwner(color);
    cout << color << " player successfully claimed Edge " << targetEdge.getIdx() << "." << endl;

    goals.push_back(targetEdge.getIdx());

    return true;
}

void Player::addVictoryPoints(int points)
{
    victoryPoints += points;
}

void Player::printStatus() const
{
    cout << color << " has " << victoryPoints << " victory points, "
         << getResourceCount("CAFFEINE") << " caffeines, "
         << getResourceCount("LAB") << " labs, "
         << getResourceCount("LECTURE") << " lectures, "
         << getResourceCount("TUTORIAL") << " tutorials, and "
         << getResourceCount("STUDY") << " studies." << endl;
}

void Player::printCompletions(Vertex *allVertices[], int numVertices) const
{
    int assignments = 0, midterms = 0, exams = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        Vertex *vertex = allVertices[i];
        if (vertex && vertex->getName() == color)
        {
            string houseLevel = vertex->getHouseLevel();
            if (houseLevel == "Assignment")
            {
                ++assignments;
            }
            else if (houseLevel == "Midterm")
            {
                ++midterms;
            }
            else if (houseLevel == "Exam")
            {
                ++exams;
            }
        }
    }
    cout << assignments << " 1 " << endl << midterms << " 2 " << endl << exams << " 3" << endl;
}

std::vector<int> Player::getGoals() { return goals; }

std::vector<std::pair<int, int>> Player::getCriteria() { return criteria; }

void Player::loadState(const int* resourceCounts, const std::string& color, int victoryPoints,
                       const std::vector<int>& goals, const std::vector<std::pair<int, int>>& criteria) {
    this->color = color;
    this->victoryPoints = victoryPoints;

    for (int i = 0; i < NUM_RESOURCES; ++i) {
        resources[i].count = resourceCounts[i];
    }

    this->goals.clear();
    this->goals.insert(this->goals.end(), goals.begin(), goals.end());

    this->criteria.clear();
    for (const auto& criterion : criteria) {
        this->criteria.push_back(criterion);
    }
}

void Player::setVP(int vp) {
    victoryPoints = vp;
}