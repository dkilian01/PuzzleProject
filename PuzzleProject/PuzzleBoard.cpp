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
void PuzzleBoard::move(int x, int y) {
	if ((abs(mx - x) + abs(my - y)) == 1) {
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