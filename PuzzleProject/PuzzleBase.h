#pragma once
#include <vector>

/**
 * @brief Klasa bazowa dla gry Puzzle.
 */
class PuzzleBase {
public:
    virtual void move(int x, int y) = 0;
    virtual bool isSolved() const = 0;
    virtual ~PuzzleBase() {}
};