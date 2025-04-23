#include "PuzzleBoard.h"
#include<algorithm>
using namespace std;
PuzzleBoard::PuzzleBoard(int size) {
	board.resize(size, vector<int>(size));// Tworzy kwadratow¹ planszê o rozmiarze size x size
	int v = 1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = v++;// Wype³nia planszê wartoœciami od 1 do n*n
}
void PuzzleBoard::changeBoard()
{
	vector<int> tiles;

		tiles.clear();
		for (auto r : board)
			for (int v : r)
				tiles.push_back(v); // Przepisuje wszystkie wartoœci do jednowymiarowego wektora

		random_device rd;
		mt19937 g(rd());
		shuffle(tiles.begin(), tiles.end(), g);//miesza pozycje w vektorze od begin do end
		int index = 0;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board.size(); j++) {
				board[i][j] = tiles[index];
				index++;
			}
		}

	stateManager.saveState(board);
	startTimer();
}
void PuzzleBoard::move(int index) {

	if (solved) return;
	int size = board.size();
	int x = index / size;
	int y = index % size;

	if ((x > 0 && board[x - 1][y] == size * size)) {// Puste pole powy¿ej  
		stateManager.saveState(board);
		swap(board[x - 1][y], board[x][y]);
	}
	if ((x < size-1 && board[x + 1][y] == size * size)) {// Puste pole ponizej  
		stateManager.saveState(board);
		swap(board[x + 1][y], board[x][y]);
	}
	if ((y > 0 && board[x][y-1] == size * size)) {// Puste pole po lewej 
		stateManager.saveState(board);
		swap(board[x][y - 1], board[x][y]);
	}
	if ((y < size - 1 && board[x][y+1] == size * size)) {// Puste pole po prawej
		stateManager.saveState(board);
		swap(board[x][y + 1], board[x][y]);
	}
}
bool PuzzleBoard::isSolved() {
	int v=1;
	for (const auto r : board) {
		for (const auto c : r) {
			if (c != v++)return false;
			
		}
	}
	solved = true;
	return solved;
}
void PuzzleBoard::startTimer() {
	startTime = chrono::steady_clock::now();
}
double PuzzleBoard::getTime() {
	auto now = chrono::steady_clock::now();
	chrono::duration<double> between = now - startTime;
	return between.count();
}

bool PuzzleBoard::canUndo() const {
	return stateManager.canUndo();
}

bool PuzzleBoard::canRedo() const {
	return stateManager.canRedo();
}

void PuzzleBoard::undoMove() {
	if (stateManager.canUndo()) {
		board = stateManager.undo(board);
	}
}

void PuzzleBoard::redoMove() {
	if (stateManager.canRedo()) {
		board = stateManager.redo(board);
	}
}

void PuzzleBoard::saveState(const string& filename) {
	stateManager.saveToFile(filename, board,getTime());
}

bool PuzzleBoard::loadState(const string& filename) {
	double time;
	if (stateManager.loadFromFile(filename, board, time))
	{
		using clock = std::chrono::steady_clock;
		startTime = clock::now() - std::chrono::duration_cast<clock::duration>(std::chrono::duration<double>(time));
		return true;

	}
	return false;
}
