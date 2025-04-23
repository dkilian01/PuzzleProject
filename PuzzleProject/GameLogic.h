#pragma once
#include "PuzzleBase.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>

class GameLogic {
public:
    GameLogic(unique_ptr<PuzzleBase> board, Player player);

    void start();
    void reset();
    void move(int index);
    bool isSolved() const;
    double getTime() const;

    bool canUndo() const;
    bool canRedo() const;
    void undo();
    void redo();

    void saveState();
    bool loadState();

    vector<vector<int>> getBoard() const;
    int getSize() const;
    string getBoardType() const;
    int getMaxTileValue() const;

    Player& getPlayer();
    string getPlayerName() const;
    void recordWin(double time);
    void persist();

    vector<int> solve();

private:
    unique_ptr<PuzzleBase> board;
    Player player;
    string boardType;
    string saveFileName() const;
};
