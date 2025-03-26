#include "HexBoard.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
using namespace std;
HexBoard::HexBoard(int size) : size(size), empty1({ -1, -1 }), empty2({ -1, -1 }) {
    int totalRows = size - 1;
    board.resize(totalRows);

    int val = 1;
    for (int i = 0; i < totalRows; ++i) {
        int rowLength = size + (i < size ? i : totalRows - 1 - i);
        board[i].resize(rowLength);
        for (int j = 0; j < rowLength; ++j) {
            board[i][j] = val++;
        }
    }

    empty1 = { totalRows - 1, board[totalRows - 1].size() - 2 };
    empty2 = { totalRows - 1, board[totalRows - 1].size() - 1 };
    board[empty1.first][empty1.second] = 0;
    board[empty2.first][empty2.second] = 0;
    startTimer();
}

void HexBoard::changeBoard() {
    stateManager.saveState(board);
    std::shuffle(board.begin(), board.end(), std::default_random_engine(std::random_device{}()));
}

void HexBoard::move(int x, int y) {
    stateManager.saveState(board);
    std::swap(board[x][y], board[empty1.first][empty1.second]);
    empty1 = { x, y };
}

bool HexBoard::isSolved()const {
	int v = 1;
	for (const auto r : board) {
		for (const auto c : r) {
			if (c != v++)return false;

		}
	}
	return true;
}
void HexBoard::startTimer() {
	startTime = chrono::steady_clock::now();
}
double HexBoard::getTime() {
	auto now = chrono::steady_clock::now();
	chrono::duration<double> between = now - startTime;
	return between.count();
}

bool HexBoard::canUndo() const {
	return stateManager.canUndo();
}

bool HexBoard::canRedo() const {
	return stateManager.canRedo();
}

void HexBoard::undoMove() {
	if (stateManager.canUndo()) {
		board = stateManager.undo(board);
	}
}

void HexBoard::redoMove() {
	if (stateManager.canRedo()) {
		board = stateManager.redo(board);
	}
}

void HexBoard::saveState(const string& filename) {
	stateManager.saveToFile(filename, board);
}

bool HexBoard::loadState(const string& filename) {
	return stateManager.loadFromFile(filename, board);
}
int HexBoard::getX()
{
	
}
int HexBoard::getY()
{
	
}

