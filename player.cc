#include "player.h"

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
    return -1; 
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

    requester.resources[requesterIndex].count -= 1;
    accepter.resources[accepterIndex].count -= 1;

    requester.resources[accepterIndex].count += 1;
    accepter.resources[requesterIndex].count += 1;

    cout << requester.getColor() << " player traded " << resource1
         << " with " << accepter.getColor() << " player for " << resource2 << "." << endl;

    return true;
}

bool Player::buildCriterion(Vertex &targetVertex, std::shared_ptr<Edge> connectedEdges[], int numEdges) {
    const int CAFFEINE_REQUIRED = 1;
    const int LAB_REQUIRED = 1;
    const int LECTURE_REQUIRED = 1;
    const int TUTORIAL_REQUIRED = 1;

    // Check if the target vertex is available
    if (!targetVertex.isAvailable()) {
        cerr << "Vertex " << targetVertex.getIdx() << " is not available for building." << endl;
        return false;
    }

    // Check if all connected vertices are available
    for (int i = 0; i < numEdges; ++i) {
        auto edge = connectedEdges[i]; // Use shared_ptr instead of raw pointer
        if (edge) {
            auto vertArr = edge->getVertices();
            auto vertex1 = vertArr[0];
            auto vertex2 = vertArr[1];

            if (vertex1.get() == &targetVertex && vertex2->getName() != "") {
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << " because it's connected to Vertex " << vertex2->getIdx() << " which is already owned." << endl;
                return false;
            } else if (vertex2.get() == &targetVertex && vertex1->getName() != "") {
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << " because it's connected to Vertex " << vertex1->getIdx() << " which is already owned." << endl;
                return false;
            }
        }
    }

    // Check if the player has enough resources
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

    // Build the criterion
    targetVertex.setOwner(color);              // Assign ownership to the player
    targetVertex.setHouseLevel("Assignment"); // Set house level to Assignment
    addVictoryPoints(1);                       // Add a victory point

    cout << color << " player successfully built a criterion (Assignment) on Vertex "
         << targetVertex.getIdx() << "." << endl;

    return true;
}


bool Player::buildCriterion2(Vertex &targetVertex, std::shared_ptr<Edge> connectedEdges[], int numEdges) {
    const int CAFFEINE_REQUIRED = 1;
    const int LAB_REQUIRED = 1;
    const int LECTURE_REQUIRED = 1;
    const int TUTORIAL_REQUIRED = 1;

    // Check if the target vertex is available
    if (!targetVertex.isAvailable()) {
        cerr << "Vertex " << targetVertex.getIdx() << " is not available for building." << endl;
        return false;
    }

    // Check if the player owns an adjacent edge connected to the target vertex
    bool ownsAdjacentEdge = false;
    for (int i = 0; i < numEdges; ++i) {
        auto edge = connectedEdges[i]; // Use shared_ptr instead of raw pointer
        if (edge) {
            auto vertArr = edge->getVertices(); // Assuming getVertices() returns shared_ptr<Vertex>[]
            if (vertArr[0].get() == &targetVertex || vertArr[1].get() == &targetVertex) {
                if (edge->getName() == color) { // Check if the edge is owned by the player
                    ownsAdjacentEdge = true;
                    break;
                }
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
        auto edge = connectedEdges[i];
        if (edge) {
            auto vertArr = edge->getVertices();
            auto vertex1 = vertArr[0];
            auto vertex2 = vertArr[1];

            if (vertex1.get() == &targetVertex && !vertex2->isAvailable()) {
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << ". Adjacent vertex (" << vertex2->getIdx() << ") is already owned." << endl;
                return false;
            }
            if (vertex2.get() == &targetVertex && !vertex1->isAvailable()) {
                cerr << "Cannot build on Vertex " << targetVertex.getIdx()
                     << ". Adjacent vertex (" << vertex1->getIdx() << ") is already owned." << endl;
                return false;
            }
        }
    }

    // Check if the player has enough resources
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
    removeResources("LECTURE", CAFFEINE_REQUIRED);
    removeResources("TUTORIAL", CAFFEINE_REQUIRED);

    // Build the criterion
    targetVertex.setOwner(color);              // Assign ownership to the player
    targetVertex.setHouseLevel("Assignment"); // Set house level to Assignment
    addVictoryPoints(1);                       // Add victory point
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
        addVictoryPoints(1); 
        cout << color << " player upgraded criterion to Midterm on Vertex "
             << targetVertex.getIdx() << "." << endl;
    }
    else if (currentLevel == "Midterm")
    {

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
        addVictoryPoints(1); 
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
                criterion.second = 2; 
            }
            else if (currentLevel == "Midterm")
            {
                criterion.second = 3; 
            }
            break;
        }
    }

    return true;
}

bool Player::claimEdge(Edge &targetEdge, std::shared_ptr<Edge> allEdges[], int numEdges) {
    const int TUTORIAL_COST = 1;
    const int STUDY_COST = 1;

    // Check if the target edge is available
    if (!targetEdge.isAvailable()) {
        cerr << "Edge " << targetEdge.getIdx() << " is already owned by another player." << endl;
        return false;
    }

    // Check if the player has enough resources
    if (getResourceCount("TUTORIAL") < TUTORIAL_COST || getResourceCount("STUDY") < STUDY_COST) {
        cerr << "You do not have enough resources." << endl;
        return false;
    }

    // Check if the player can claim the edge
    bool canClaim = false;
    auto vertArr = targetEdge.getVertices(); // Assuming getVertices() returns an array of shared_ptr<Vertex>
    for (int i = 0; i < 2; ++i) {
        auto vertex = vertArr[i]; // shared_ptr<Vertex>
        if (vertex && vertex->getName() == color) {
            // Player owns a connected criterion
            canClaim = true;
            break;
        }

        // Check adjacent edges
        for (int j = 0; j < numEdges; ++j) {
            auto adjacentEdge = allEdges[j]; // shared_ptr<Edge>
            if (adjacentEdge.get() != &targetEdge) { 
                auto adjVertArr = adjacentEdge->getVertices(); // Assuming this returns shared_ptr<Vertex>[]
                if (adjVertArr[0] == vertex || adjVertArr[1] == vertex) {
                    if (adjacentEdge->getName() == color) {
                        // Player owns an adjacent edge
                        canClaim = true;
                        break;
                    }
                }
            }
        }

        if (canClaim) {
            break;
        }
    }

    if (!canClaim) {
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
