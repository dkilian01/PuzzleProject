#include "HexPuzzle.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;

HexPuzzle::HexPuzzle(int size) : size(size) {
    int rows = size - 1;
    board.resize(rows);
    int value = 1;

    for (int i = 0; i < rows; ++i) {
        int rowLength = (i == 0 || i == rows - 1) ? size : size + 2;
        board[i].resize(rowLength);
        for (int j = 0; j < rowLength; ++j) {
            board[i][j] = value++;
        }
    }

    // Dwa ostatnie wartoœci (puste pola)
    board[rows - 1][board[rows - 1].size() - 2] = size * size - 1;
    board[rows - 1][board[rows - 1].size() - 1] = size * size;

    
}
void HexPuzzle::move(int index) {
    auto [x, y] = indexToCoord(index);
    if (!isValid(x, y)) return;
    if (board[x][y] == size * size || board[x][y] == (size * size - 1)) return;

    stateManager.saveState(board);

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            int val = board[i][j];
            if ((val == size * size || val == size * size - 1) &&
                isUpTriangle(i, j) == isUpTriangle(x, y) &&
                areNeighbors({ x, y }, { i, j }))
            {
                swap(board[x][y], board[i][j]);
                return;
            }
        }
    }
}

bool HexPuzzle::isSolved() const {
    int val = 1;
    for (const auto& row : board)
        for (int v : row)
            if (v != 0 && v != val++) return false;
    return true;
}

void HexPuzzle::changeBoard() {
    vector<int> tiles;
    for (auto& row : board)
        for (int val : row)
            if (val != size * size && val != size * size - 1)
                tiles.push_back(val);

    shuffle(tiles.begin(), tiles.end(), default_random_engine(random_device{}()));

    int idx = 0;
    for (auto& row : board)
        for (int& val : row)
            if (val != size * size && val != size * size - 1)
                val = tiles[idx++];

    // Puste pola s¹ zawsze na koñcu w ostatnim rzêdzie
    int r = board.size() - 1;
    board[r][board[r].size() - 2] = size * size - 1;
    board[r][board[r].size() - 1] = size * size;

    stateManager.saveState(board);
    startTimer();
}

void HexPuzzle::startTimer() {
    startTime = chrono::steady_clock::now();
}

double HexPuzzle::getTime() {
    auto now = chrono::steady_clock::now();
    chrono::duration<double> between = now - startTime;
    return between.count();
}

void HexPuzzle::undoMove() {
    if (stateManager.canUndo()) {
        board = stateManager.undo(board);
    }
}

void HexPuzzle::redoMove() {
    if (stateManager.canRedo()) {
        board = stateManager.redo(board);
    }
}

void HexPuzzle::saveState(const string& filename) {
    stateManager.saveToFile(filename, board);
}

bool HexPuzzle::loadState(const string& filename) {
    return stateManager.loadFromFile(filename, board);
}
bool HexPuzzle::isUpTriangle(int i, int j) const {
    return (i + j) % 2 == 0;
}

bool HexPuzzle::isValid(int i, int j) const {
    return i >= 0 && i < board.size() && j >= 0 && j < board[i].size();
}

bool HexPuzzle::areNeighbors(pair<int, int> a, pair<int, int> b) const {
    static const vector<pair<int, int>> dirs = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, 1}, {1, -1}
    };
    for (const auto& [dx, dy] : dirs) {
        if (a.first + dx == b.first && a.second + dy == b.second)
            return true;
    }
    return false;
}

pair<int, int> HexPuzzle::indexToCoord(int index) const {
    int current = 0;
    for (int i = 0; i < board.size(); ++i) {
        if (index < current + board[i].size()) {
            return { i, index - current };
        }
        current += board[i].size();
    }
    return { -1, -1 };
}