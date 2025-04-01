#pragma once
#include "PuzzleBase.h"
#include "GameStateManager.h"
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
    //vector<vector<vector<int>>> history;
    //int currentStep = -1;
    GameStateManager<vector<vector<int>>> stateManager;
    int mx, my;
    chrono::time_point<chrono::steady_clock> startTime;
public:
    PuzzleBoard(int size);
    void move(int index) override;
    bool isSolved() const override;
    int getSize() { return board.size(); }
    vector<vector<int>> getBoard() const override { return board; }
    void changeBoard();

    void startTimer() override;
    double getTime()  override;

    bool canUndo() const override;
    bool canRedo() const override;
    void undoMove() override;
    void redoMove() override;
    //int getStep();

    void saveState(const string& filename) override;
    bool loadState(const string& filename) override;
    int getX()override;
    int getY()override;
    
};

