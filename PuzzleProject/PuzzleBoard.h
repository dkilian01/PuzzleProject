#pragma once
#include "PuzzleBase.h"
#include <vector>
#include <chrono>
#include <random>
#include <fstream> 
using namespace std;
class PuzzleBoard :
    public PuzzleBase
{
private:
    vector<vector<int>> board;
    vector<vector<vector<int>>> history;
    int currentStep = -1;
    int mx, my;
    chrono::time_point<chrono::steady_clock> startTime;
public:
    PuzzleBoard(int size);
    void move(int x, int y) override;
    bool isSolved() const override;
    int getSize() { return board.size(); }
    vector<vector<int>> getBoard() { return board; }
    void changeBoard();

    void startTimer();
    double getTime();

    bool canUndo() const;
    bool canRedo() const;
    void undoMove();
    void redoMove();
    int getStep();

    void saveState(const string& filename);
    bool loadState(const string& filename);
};

