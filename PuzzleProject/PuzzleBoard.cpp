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
	history.clear();
	currentStep = -1;
	history.push_back(board);
	currentStep = 0;
	startTimer();
}
void PuzzleBoard::move(int x, int y) {
	if ((abs(mx - x) + abs(my - y)) == 1) {
		if (currentStep < (int)history.size() - 1) {
			history.erase(history.begin() + currentStep + 1, history.end());
		}

		history.push_back(board);
		currentStep++;

		swap(board[mx][my], board[x][y]);
		mx = x;
		my = y;

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
	return currentStep >= 0;
}

bool PuzzleBoard::canRedo() const {
	return currentStep < (int)history.size() - 1;
}

void PuzzleBoard::undoMove() {
	if (canUndo()) {
		board = history[currentStep];
		currentStep--;

		for (int i = 0; i < board.size(); ++i)
			for (int j = 0; j < board.size(); ++j)
				if (board[i][j] == board.size() * board.size()) {
					mx = i; my = j;
				}
	}
}

void PuzzleBoard::redoMove() {
	if (canRedo()) {
		currentStep++;
		board = history[currentStep];

		for (int i = 0; i < board.size(); ++i)
			for (int j = 0; j < board.size(); ++j)
				if (board[i][j] == board.size() * board.size()) {
					mx = i; my = j;
				}
	}
}

void PuzzleBoard::saveState(const string& filename) {
	ofstream out(filename);
	out << board.size() << "\n";
	for (auto& row : board)
		for (int v : row)
			out << v << " ";
	out.close();
}

bool PuzzleBoard::loadState(const string& filename) {
	ifstream in(filename);
	if (!in) return false;
	int size;
	in >> size;
	board.resize(size, vector<int>(size));
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			in >> board[i][j];
			if (board[i][j] == size * size) {
				mx = i; my = j;
			}
		}
	in.close();
	history.clear();
	currentStep = -1;
	startTimer();
	return true;
}
int PuzzleBoard::getStep() {
	return currentStep;
}
