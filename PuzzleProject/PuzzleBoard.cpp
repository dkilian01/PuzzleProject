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