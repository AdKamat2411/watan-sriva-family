#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm> // For std::find

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o); // Add the shared_ptr directly
}

void Subject::detach(std::shared_ptr<Observer> o) {
    auto it = std::find(observers.begin(), observers.end(), o); // Find the shared_ptr
    if (it != observers.end()) {
        observers.erase(it); // Remove it from the vector
    }
}

void Subject::notifyObservers(int rollSum, std::vector<Player*>& players, int currTurn) {
    for (const auto& observer : observers) { // Iterate over shared_ptr
        observer->notify(rollSum, players, currTurn); // Use the Observer's notify method
    }
}

std::vector<std::shared_ptr<Observer>> Subject::getObservers() {
    return observers; // Return the vector of shared_ptr
}
