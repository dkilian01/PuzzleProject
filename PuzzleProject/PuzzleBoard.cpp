#include "PuzzleBoard.h"
#include<algorithm>
using namespace std;
PuzzleBoard::PuzzleBoard(int size) {
	board.resize(size, vector<int>(size));
	int v = 1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = v++;
	//board[size - 1][size - 1] = 0; //moze zmienic zeby sprawdzac wartosc maksymalna wtedy przy rozwiazaniu nie trzeba by sprawdzac ostatniego pola
	mx = size - 1;
	my = size - 1;
}
void PuzzleBoard::changeBoard()
{
	vector<int> tiles;

	for (auto r : board)
		for (int v : r)
			tiles.push_back(v);

	random_device rd;
	mt19937 g(rd());
	shuffle(tiles.begin(), tiles.end(), g);
	int index = 0;
	for (int i = 0; i < board.size();i++) {
		for (int j = 0; j < board.size();j++) {
			board[i][j] = tiles[index];
			if (tiles[index] == board.size() * board.size())
			{
				mx = i;
				my = j;
			}
			index++;
		}
	}
	startTimer();
}
void PuzzleBoard::move(int index) {
	/*if ((abs(mx - x) + abs(my - y)) == 1) {
		stateManager.saveState(board);
		swap(board[mx][my], board[x][y]);
		mx = x;
		my = y;*/

	
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
bool PuzzleBoard::isSolved()const {
	int v=1;
	for (const auto r : board) {
		for (const auto c : r) {
			if (c != v++)return false;
			
		}
	}
	return true;
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
	stateManager.saveToFile(filename, board);
}

bool PuzzleBoard::loadState(const string& filename) {
	return stateManager.loadFromFile(filename, board);
}
int PuzzleBoard::getX()
{
	return mx;
}
int PuzzleBoard::getY()
{
	return my;
}
