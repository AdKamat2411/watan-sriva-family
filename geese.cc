#include "geese.h"

geese::geese(int currTile): currTile(currTile) {}

void geese::moveGeese(int newTile, Tile** tileArr) {
    tileArr[currTile]->updateGeese();
    tileArr[newTile]->updateGeese();
}

void geese::stealResource(GameManager* g) {
    cout << "Choose where to place the GEESE." << endl;
    int geeseTile;
    cin >> geeseTile;

    std::vector<Player*> players = g->getPlayers();

    string currPlayer = g->getCurrentPlayer();

    Player* currentPlayer;

    for (int i = 0; i < 4; i++) {
        if (currPlayer == players[i]->getColor()) {
            currentPlayer = players[i];
            break;
        }
    }

    vector <string> playersOnTile;
    Tile* tile = g->getBoard()->getTile(geeseTile);
    Vertex** vertArr = tile->getAdjacentVertices();

    for (int i = 0; i < 6; i++) {
        if (!vertArr[i]->isAvailable()) {
            playersOnTile.push_back(vertArr[i]->getName());
        }
    }

    if (playersOnTile.empty()) {
        cout << "Student " << currPlayer << " has no students to steal from." << endl;
        return;
    }

    for (const string& p : playersOnTile) {
        cout << "Student" <<  currPlayer << "can choose to steal from" << p << "." << endl;
    }

    cout << "Choose a student to steal from." << endl;

    string targetPlayer;

    while (true) {
        cin >> targetPlayer;

        if (find(playersOnTile.begin(), playersOnTile.end(), targetPlayer) != playersOnTile.end()) {
            break;
        }

        cout << "Invalid choice. Please choose a valid student to steal from: ";
    }

    Player* target;

    for (int i = 0; i < 4; i++) {
        if (targetPlayer == players[i]->getColor()) {
            target = players[i];
            break;
        }
    }

    int totalResources = 0;
    vector<string> resourceNames = {"CAFFEINE", "LAB", "LECTURE", "STUDY", "TUTORIAL"};
    for (const string& resource : resourceNames) {
        totalResources += target->getResourceCount(resource);
    }

    if (totalResources == 0) {
        cout << "Student " << targetPlayer << " has no resources to steal." << endl;
        return;
    }

    vector<int> cumulativeProbabilities;
    int runningTotal = 0;
    for (const string& resource : resourceNames) {
        runningTotal += target->getResourceCount(resource);
        cumulativeProbabilities.push_back(runningTotal);
    }

    int randomValue = rand() % totalResources + 1;

    string stolenResource;
    for (size_t i = 0; i < cumulativeProbabilities.size(); ++i) {
        if (randomValue <= cumulativeProbabilities[i]) {
            stolenResource = resourceNames[i];
            break;
        }
    }

    target->removeResources(stolenResource, 1);
    currentPlayer->addResources(stolenResource, 1);

    cout << "Student " << currPlayer << " steals " << stolenResource << " from student " << targetPlayer << "." << endl;

    moveGeese(geeseTile, g->getBoard()->getTiles());
}

