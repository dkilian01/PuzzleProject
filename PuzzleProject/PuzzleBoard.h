#pragma once
#include "PuzzleBase.h"
#include <vector>
#include <chrono>
using namespace std;
class PuzzleBoard :
    public PuzzleBase
{
private:
    vector<vector<int>> board;
    int mx, my;
    chrono::time_point<chrono::steady_clock> startTime;
public:
    PuzzleBoard(int size);
    void move(int x, int y) override;
    bool isSolved() const override;
    int getSize() { return board.size(); }
    vector<vector<int>> getBoard() { return board; }

    void startTimer();
    double getTime();
};

