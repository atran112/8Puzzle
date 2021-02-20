//
//  source.cpp
//  
//
//  Created by Andre Tran on 2/13/21.
//

#include "Puzzle.hpp"

#include <stdio.h>
#include <string>

using namespace std;

bool operator<(const Puzzle& p1, const Puzzle& p2) {
    return (p1.cost + p1.heuristic) > (p2.cost + p2.heuristic); //minHeap
}


bool findSolution(const Puzzle& currPuzzle, const string& heuristicType) {
    
    int maxQSize = 0;
    int numExpanded = 0;
    
    vector<int> gridSolution {1, 2, 3, 4, 5, 6, 7, 8, 0};
    
    priority_queue<Puzzle> puzzleQ;
    //set<vector<int>> puzzleGridSet;
    
    puzzleQ.push(currPuzzle);
    //puzzleGridSet.insert(currPuzzle.grid);
    
    //cout << "Expanding State" << endl;
    
    while (!puzzleQ.empty()) {
        Puzzle currPuzzle = puzzleQ.top();
        puzzleQ.pop();
        
        ++numExpanded;
        
        if (currPuzzle.grid == gridSolution) {
            
            cout << endl << "----------" << endl << "Success!" << endl;
            currPuzzle.display(); //
            cout << "max queue size: " << maxQSize << endl;
            cout << "num expanded: " << numExpanded << endl;
            cout << "----------" << endl;
            return true;
        }
        
        currPuzzle.display(); //delete this?
        
        cout << "Expanding this Node" << endl;
        
        vector<Puzzle> nextPuzzles = currPuzzle.expandPuzzle(heuristicType); //change this to expand
        
        for (unsigned i = 0; i < nextPuzzles.size(); ++i) {
            
            puzzleQ.push(nextPuzzles.at(i));
            
        }
        
        if (maxQSize < puzzleQ.size()) {
            maxQSize = puzzleQ.size();
        }
        
        //cout << "The best state to expand with a g(n) = " << currPuzzle.cost << " and h(n) = " << currPuzzle.heuristic << " is..." << endl;
        
    }
    
    cout << "failure" << endl;
    return false;
    
}

int main() {
    
    cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle." << endl;
    
    string puzzleType;
    
    cin >> puzzleType;
    
    vector<int> grid;
    
    if (puzzleType == "1") {
        
        cout << "Using default puzzle" << endl;
        
        cout << "Puzzle set to ";
        
//        cout << "depth 1" << endl;
//        grid = {1, 2, 3, 4, 5, 6, 7, 0, 8};
//
//        cout << "depth 2" << endl;
//        grid = {1, 2, 3, 4, 5, 6, 0, 7, 8};
//
//        cout << "depth 4" << endl;
//        grid = {1, 2, 3, 5, 0, 6, 4, 7, 8};
//
//        cout << "depth 8" << endl;
//        grid = {1, 3, 6, 5, 0, 2, 4, 7, 8};
//
//        cout << "depth 12" << endl;
//        grid = {1, 3, 6, 5, 0, 7, 4, 8, 2};
//
//        cout << "depth 16" << endl;
//        grid = {1, 6, 7, 5, 0, 3, 4, 8, 2};
        
        cout << "depth 20" << endl;
        grid = {7, 1, 2, 4, 8, 5, 6, 3, 0};
        
//        cout << "depth 24" << endl;
//        grid = {0, 7, 2, 4, 6, 1, 3, 5, 8};
        
        cout << endl;
    }
    
    else {
        
        cout << "Enter your puzzle, use a zero to represent the blank" << endl;
        cout << "Please enter three numbers at a time, then press enter" << endl;
        
        string row = "";
        
        for (unsigned i = 0; i < 3; ++i) {
            
            cin >> row;
            
            cout << row << endl;
            
            for (unsigned j = 0; j < row.size(); ++j) {
                int num = (int) row.at(j) - 48;
                grid.push_back(num);
                
                cout << num <<endl;
            }
        }
    }
    
    cout << "Enter your choice of algorithm." << endl;
    cout << '\t' << "1. Uniform Cost Search" << endl;
    cout << '\t' << "2. A* with the Misplaced Tile heuristic" << endl;
    cout << '\t' << "3. A* with the Manhattan distance heuristic" << endl;
    
    string heuristicType = "";
    
    cin >> heuristicType;
    
    if (heuristicType == "1") {
        heuristicType = "None";
    }
    
    else if (heuristicType == "2") {
        heuristicType = "Misplaced Tiles";
    }
    
    else if (heuristicType == "3") {
        heuristicType = "Manhattan Distance";
    }
    
    else {
        cout << "Invalid number. Defaulting to Manhattan Distance." << endl;
        heuristicType = "Manhattan Distance";
    }
    
    Puzzle userPuzzle(grid, heuristicType);
    
    findSolution(userPuzzle, heuristicType);
    
    
    
    return 0;
}
