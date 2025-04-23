
#include "GameLogic.h"
#include "PuzzleBoard.h"
#include "HexPuzzle.h"
#include <fstream>
#include <sstream>
using namespace std;
GameLogic::GameLogic(std::unique_ptr<PuzzleBase> board, Player player)
    : board(std::move(board)), player(std::move(player)) {
    // Okreœlenie typu planszy – dynamiczne sprawdzenie, czy to PuzzleBoard (klasyczna)
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

// Zwraca maksymaln¹ wartoœæ kafelka, w zale¿noœci od typu planszy
int GameLogic::getMaxTileValue() const {
    // Jeœli plansza to HexPuzzle – pobierz przez metodê getTileAmount()
    if (auto* hex = dynamic_cast<HexPuzzle*>(board.get())) {
        return hex->getTileAmount();
    }
    else {
        // Dla klasycznej planszy: maksymalna wartoœæ = rozmiar * rozmiar
        int size = board->getSize();
        return size * size;
    }
}
string GameLogic::saveFileName() const {
    // Format: <nazwa_gracza>_<rozmiar>_<typ>_save.txt
    return player.getPlayerName() + "_" + std::to_string(board->getSize()) + "_" + boardType + "_save.txt";
}