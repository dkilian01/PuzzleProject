#pragma once
#include <vector>
#include<string>
/**
 * @brief Klasa bazowa dla gry Puzzle.
 */
class PuzzleBase {
public:
    virtual void move(int index) = 0;
    virtual bool isSolved() = 0;
    virtual std::vector<std::vector<int>> getBoard() const = 0;

    virtual void startTimer() = 0;
    virtual double getTime()  { return 0.0; }

    virtual void undoMove() = 0;
    virtual void redoMove() = 0;
    virtual bool canUndo() const { return false; }
    virtual bool canRedo() const { return false; }
    virtual void changeBoard() = 0;

    virtual void saveState(const std::string&) {}
    virtual bool loadState(const std::string&) { return false; }
    virtual ~PuzzleBase() {}
    virtual int getSize() const = 0;
protected:
    bool solved = false;
    
    
};