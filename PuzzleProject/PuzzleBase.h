#pragma once
#include <vector>
#include<string>
/**
 * @brief Klasa bazowa dla gry Puzzle.
 */
class PuzzleBase {
public:
    virtual void move(int index) = 0;
    virtual bool isSolved() const = 0;
    virtual std::vector<std::vector<int>> getBoard() const = 0;

    virtual void startTimer() {}
    virtual double getTime()  { return 0.0; }

    virtual void undoMove() {}
    virtual void redoMove() {}
    virtual bool canUndo() const { return false; }
    virtual bool canRedo() const { return false; }

    virtual void saveState(const std::string&) {}
    virtual bool loadState(const std::string&) { return false; }
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual ~PuzzleBase() {}
};