#pragma once
#include "PuzzleBoard.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;
class PuzzleSolver {
public:
    static vector<int> solve(const PuzzleBoard& puzzle);
    static bool isSolvable(const vector<vector<int>>& board);

private:
    static int manhattan(const vector<vector<int>>& board);
    static string boardToString(const vector<vector<int>>& board);
    static vector<pair<vector<vector<int>>, int>> getNeighbors(const vector<vector<int>>& board);
   
};
