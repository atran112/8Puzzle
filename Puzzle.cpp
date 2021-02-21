//
//  Puzzle.cpp
//  
//
//  Created by Andre Tran on 2/13/21.
//

#include "Puzzle.hpp"

using namespace std;

Puzzle::Puzzle() {
    
    this->grid = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    this->cost = 0;
    this->heuristic = 0;
}

Puzzle::Puzzle(const vector<int> &grid, const string& heuristicType) {
    this->grid = grid;
    this->cost = 0; //this should generally be 0
    this->position = findCurrentPosition();
    updateHeuristic(heuristicType); //I will probably need to add the heuristic type to this function
}

Puzzle& Puzzle::operator=(const Puzzle& rhs) {
    if (this != &rhs) {
        
        grid = rhs.grid;
        cost = rhs.cost;
        position = rhs.position;
        heuristic = rhs.heuristic;
    }
    
    return *this;
}

vector<Puzzle> Puzzle::expandPuzzle(const string& heuristicType) {
    vector<int> swapPositions = findPositions(); //these positions will be used to swap 0
    vector<Puzzle> nextPuzzles; //will return this to be put into the Q
    
    for (unsigned i = 0; i < swapPositions.size(); ++i) {
        
        Puzzle nextPuzzle = *this;
        
        nextPuzzle.swap(swapPositions.at(i), heuristicType);
        
        
        //if search is misplaced do misplaced function
        //else if search is manhattan distance do mh function

        nextPuzzles.push_back(nextPuzzle);
    }
    
    return nextPuzzles;
}

vector<int> Puzzle::findPositions() {
    vector<int> positions;
    
    switch (position) {
        case 0:
            positions.push_back(1);
            positions.push_back(3);
            break;
        case 1:
            positions.push_back(0);
            positions.push_back(2);
            positions.push_back(4);
            break;
        case 2:
            positions.push_back(1);
            positions.push_back(5);
            break;
        case 3:
            positions.push_back(0);
            positions.push_back(4);
            positions.push_back(6);
            break;
        case 4:
            positions.push_back(3);
            positions.push_back(1);
            positions.push_back(5);
            positions.push_back(7);
            break;
        case 5:
            positions.push_back(4);
            positions.push_back(2);
            positions.push_back(8);
            break;
        case 6:
            positions.push_back(3);
            positions.push_back(7);
            break;
        case 7:
            positions.push_back(6);
            positions.push_back(4);
            positions.push_back(8);
            break;
        case 8:
            positions.push_back(7);
            positions.push_back(5);
            break;
        default:
            //error
            cout << "error" << endl;
    }
    
    return positions;
}

void Puzzle::swap(const int& nextPosition, const string& heuristicType) {
    
    //swap values in grid
    
    grid.at(position) = grid.at(nextPosition);
    grid.at(nextPosition) = 0; //set the next positon to 0
    
    //update position
    
    position = nextPosition;
    
    //increment cost
    
    cost++;
    
    //update heuristic
    
    updateHeuristic(heuristicType);
    
}

void Puzzle::updateHeuristic(const string& heuristicType) {
    
    int sum = 0;
    
    if (heuristicType == "Misplaced Tiles") {
        
        for (unsigned i = 0; i < grid.size(); ++i) {
            
            if (grid.at(i) != ((i + 1) % 9)) {
                sum++;
            }
        }
        
    }
    
    else if (heuristicType == "Manhattan Distance") {
        
        for (unsigned i = 0; i < grid.size(); ++i) {
            int num1 = (i + 1) % 9;
            int num2 = grid.at(i);
            
            //don't caluclate for 0
            
            if (num1 != 0) {
                sum += calculateDistance(num1, num2);
            }
            
        }
        
    }
    
    
    heuristic = sum;
    
    
}

const int Puzzle::calculateDistance(int & num1, int & num2) {
    
    int sum = 0;
    
    vector<int> coord1 = getCoordinates(num1);
    vector<int> coord2 = getCoordinates(num2);
    
    for (unsigned i = 0; i < coord1.size(); ++i) {
        sum += abs(coord1.at(i) - coord2.at(i));
    }
    
    return sum;
}

vector<int> Puzzle::getCoordinates(int & num) {
    
    vector<int> coordinates;
    
    switch (num) {
        case 1:
            coordinates.push_back(1);
            coordinates.push_back(1);
            break;
        case 2:
            coordinates.push_back(1);
            coordinates.push_back(2);
            break;
        case 3:
            coordinates.push_back(1);
            coordinates.push_back(3);
            break;
        case 4:
            coordinates.push_back(2);
            coordinates.push_back(1);
            break;
        case 5:
            coordinates.push_back(2);
            coordinates.push_back(2);
            break;
        case 6:
            coordinates.push_back(2);
            coordinates.push_back(3);
            break;
        case 7:
            coordinates.push_back(3);
            coordinates.push_back(1);
            break;
        case 8:
            coordinates.push_back(3);
            coordinates.push_back(2);
            break;
        case 0:
            coordinates.push_back(3);
            coordinates.push_back(3);
            break;
        default:
            cout << " error" << endl;
    }
    
    return coordinates;
}

int Puzzle::findCurrentPosition() const {
    for (unsigned i = 0; i < grid.size(); ++i) {
        if (grid.at(i) == 0) {
            return i;
        }
    }
    
    cout << "error, returning -1" << endl;
    return -1;
}

void Puzzle::display() const {
    for (unsigned i = 0; i < grid.size(); ++i) {
        if (i % 3 == 0) {
            cout << endl;
        }
        cout << grid.at(i);
    }
    
    cout << endl;
    cout << "g(n) = " << cost << endl;
    cout << "h(n) = " << heuristic << endl;
}
