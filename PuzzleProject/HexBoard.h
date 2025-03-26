#pragma once
#include "PuzzleBase.h"
#include "GameStateManager.h"
#include <vector>
#include <chrono>
using namespace std;
class HexBoard : public PuzzleBase {
private:
    vector<vector<int>> board;
    GameStateManager<vector<vector<int>>> stateManager;
    pair<int, int> empty1, empty2;
    int size;
    chrono::time_point<chrono::steady_clock> startTime;

public:
    HexBoard(int size);
    void move(int x, int y) override;
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
    int getX() override;
    int getY() override;
};
