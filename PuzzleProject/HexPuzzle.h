#pragma once
#include "PuzzleBase.h"
#include "GameStateManager.h"
#include <vector>
#include <chrono>
using namespace std;


class HexPuzzle : public PuzzleBase {
private:
    vector<vector<int>> board;
    GameStateManager<vector<vector<int>>> stateManager;
    pair<int, int> empty1, empty2;
    int size;
    int tileAmount;
    
    chrono::time_point<chrono::steady_clock> startTime;

    bool isUpTriangle(int i, int j) const;
    bool isValid(int i, int j) const;
    pair<int, int> indexToCoord(int index) const;
   

public:
    HexPuzzle(int size);
    void move(int index) override;
    bool isSolved() const override;
    std::vector<std::vector<int>> getBoard() const override { return board; }

    void changeBoard();
    void startTimer() override;
    double getTime() override;

    bool canUndo() const override { return stateManager.canUndo(); }
    bool canRedo() const override { return stateManager.canRedo(); }
    void undoMove() override;
    void redoMove() override;

    void saveState(const std::string& filename) override;
    bool loadState(const std::string& filename) override;
    int getX() override { return empty1.first; }
    int getY() override { return empty1.second; }
    int getTileAmount();

    vector<pair<int, int>> getTriangleNeighbors(int x, int y) const;
};
