//
//  Puzzle.hpp
//  
//
//  Created by Andre Tran on 2/13/21.
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <set>

using namespace std;

class Puzzle {
 public:
    vector<int> grid;
    int cost;
    int heuristic;
    int position;
    
    Puzzle();
    Puzzle(const vector<int>& grid, const string& heuristicType);
    Puzzle & operator=(const Puzzle& rhs);
    
    vector<Puzzle> expandPuzzle(const string& heuristicType);
    vector<int> findPositions(); //helper functions
    
    void swap(const int& nextPositon, const string& heuristicType);
    void updateHeuristic(const string& heuristicType);
    
    const int calculateDistance(int & num1, int & num2);
    vector<int> getCoordinates(int & val);
    int findCurrentPosition() const;
    
    void display() const; // display the puzzle
};

#endif /* Puzzle_hpp */
