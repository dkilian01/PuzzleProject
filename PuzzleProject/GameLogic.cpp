#include "GameLogic.h"
#include "PuzzleSolver.h"
#include "PuzzleBoard.h"
#include "HexPuzzle.h"
#include <fstream>
#include <sstream>
using namespace std;
GameLogic::GameLogic(std::unique_ptr<PuzzleBase> board, Player player)
    : board(std::move(board)), player(std::move(player)) {
    boardType = dynamic_cast<PuzzleBoard*>(this->board.get()) ? "classic" : "hex";
}

void GameLogic::start() {
    board->startTimer();
}

void GameLogic::reset() {
    board->changeBoard();
}

void GameLogic::move(int index) {
    board->move(index);
}

bool GameLogic::isSolved() const {
    return board->isSolved();
}

double GameLogic::getTime() const {
    return board->getTime();
}

bool GameLogic::canUndo() const {
    return board->canUndo();
}

bool GameLogic::canRedo() const {
    return board->canRedo();
}

void GameLogic::undo() {
    board->undoMove();
}

void GameLogic::redo() {
    board->redoMove();
}

void GameLogic::saveState() {
    board->saveState(saveFileName());
}

bool GameLogic::loadState() {
    std::ifstream testFile(saveFileName());
    if (!testFile.good()) {
        return false;
    }
    return board->loadState(saveFileName());
}

vector<vector<int>> GameLogic::getBoard() const {
    return board->getBoard();
}

int GameLogic::getSize() const {
    return board->getSize();
}

string GameLogic::getBoardType() const {
    return boardType;
}

Player& GameLogic::getPlayer() {
    return player;
}

string GameLogic::getPlayerName() const {
    return player.getPlayerName();
}

void GameLogic::recordWin(double time) {
    player.setScore(time, board->getSize(), boardType);
}

void GameLogic::persist() {
    player.saveToFile();
}





int GameLogic::getMaxTileValue() const {
    if (auto* hex = dynamic_cast<HexPuzzle*>(board.get())) {
        return hex->getTileAmount();
    }
    else {
        int size = board->getSize();
        return size * size;
    }
}
string GameLogic::saveFileName() const {
    return player.getPlayerName() + "_" + std::to_string(board->getSize()) + "_" + boardType + "_save.txt";
}