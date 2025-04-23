#include "HexPuzzle.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QTextStream>
using namespace std;

HexPuzzle::HexPuzzle(int size) : size(size) {
    int rows = size - 1;
    board.resize(rows);

    tileAmount = 1;
    for (int i = 0; i < rows; ++i) {
        int layer = (i < rows / 2) ? i : rows - 1 - i;
        int rowLength = size + 2 * layer;

        board[i].resize(rowLength);
        for (int j = 0; j < rowLength; ++j) {
            board[i][j] = tileAmount++;
        }
    }
    int lastRow = rows - 1;
    int lastCol = board[lastRow].size();

    empty1 = { lastRow, lastCol - 2 };
    empty2 = { lastRow, lastCol - 1 };

    board[empty1.first][empty1.second] = tileAmount - 2;
    board[empty2.first][empty2.second] = tileAmount - 1;
}
void HexPuzzle::move(int index) {
    index++;
    if (solved)return;
    auto from = indexToCoord(index);
    if (!isValid(from.first, from.second)) {
        return;
    }

    int val = board[from.first][from.second];
    int emptyVal1 = tileAmount - 2;
    int emptyVal2 = tileAmount - 1;

    if (val == emptyVal1 || val == emptyVal2) {
        return;
    }



    

    for (const auto& neighbor : getTriangleNeighbors(from.first, from.second)) {
        if (board[neighbor.first][neighbor.second] == tileAmount-2 || board[neighbor.first][neighbor.second] == tileAmount - 1)
        {
            for (const auto& neighbor2 : getTriangleNeighbors(neighbor.first, neighbor.second))
            {
                if (board[neighbor2.first][neighbor2.second] == tileAmount-2 || board[neighbor2.first][neighbor2.second] == tileAmount - 1)
                {
                    stateManager.saveState(board);
                    swap(board[from.first][from.second], board[neighbor2.first][neighbor2.second]);
                    
                }
            }
        }
    }

}
bool HexPuzzle::isSolved()  {
    int val = 1;
    for (const auto& row : board)
        for (int v : row)
            if (v != 0 && v != val++) return false;
    solved = true;
    return solved;
}

void HexPuzzle::changeBoard() {
    vector<int> tiles1, tiles2;

    int rows = 0, s = size;
    while (rows <= size-2)
    {
        int cels = board[rows].size();
        if (rows<(size-1)/2)
        {
            for (int i = 0; i < cels; i++)
            {

                    if (i % 2 == 0)tiles1.push_back(board[rows][i]);
                    else tiles2.push_back(board[rows][i]);
                
            }
        }
        else
        {
            for (int i = 0; i < cels; i++)
            {            

                    if (i % 2 == 1)tiles1.push_back(board[rows][i]);
                    else tiles2.push_back(board[rows][i]);
                
            }
        }
        rows++;
    }
    shuffle(tiles1.begin(), tiles1.end(), default_random_engine(random_device{}()));
    shuffle(tiles2.begin(), tiles2.end(), default_random_engine(random_device{}()));
    int s1 = tiles1.size(), s2 = tiles2.size();
    int index1 = 0,index2=0;
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (i < (size - 1) / 2)
            {
                if (j % 2 == 0)board[i][j] = tiles1[index1++];
                else board[i][j] = tiles2[index2++];
            }
            else
            {
                if (j % 2 == 1)board[i][j] = tiles1[index1++];
                else board[i][j] = tiles2[index2++];
            }
            if (board[i][j] == tileAmount - 1)empty1 = { i,j };
            if (board[i][j] == tileAmount - 2)empty2 = { i,j };
        }
    }
    for (const auto& neighbor2 : getTriangleNeighbors(empty1.first, empty1.second))
    {
        if (board[neighbor2.first][neighbor2.second] != tileAmount - 2)
        {
            swap(board[empty2.first][empty2.second], board[neighbor2.first][neighbor2.second]);
        }
    }
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
    stateManager.saveToFile(filename, board,getTime());
}

bool HexPuzzle::loadState(const string& filename) {
    double time;
    if (stateManager.loadFromFile(filename, board, time))
    {
        using clock = std::chrono::steady_clock;
        startTime = clock::now() - std::chrono::duration_cast<clock::duration>(std::chrono::duration<double>(time));
        return true;

    }
    return false;
}
bool HexPuzzle::isUpTriangle(int i, int j) const {
    if (i <= (size / 2) - 1)
    {
        return(j % 2 == 0);
    }
    return(j % 2 == 1);
}

bool HexPuzzle::isValid(int i, int j) const {
    return i >= 0 && i < board.size() && j >= 0 && j < board[i].size();
}
pair<int, int> HexPuzzle::indexToCoord(int index) const {
    int rows = size - 1;
    int currentIndex = 1; 
    for (int x = 0; x < rows; ++x) {
        int len = (x < rows / 2) ? size + 2 * x : size + 2 * (rows - 1 - x);
        if (index < currentIndex + len) {
            int y = index - currentIndex;
            return { x, y };
        }
        currentIndex += len;
    }
    return { -1, -1 };
}
int HexPuzzle::getTileAmount()
{
    return tileAmount;
}
std::vector<std::pair<int, int>> HexPuzzle::getTriangleNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    if (!isValid(x, y)) return neighbors;

    bool up = isUpTriangle(x, y);

    if (isValid(x, y - 1)) neighbors.emplace_back(x, y - 1);
    if (isValid(x, y + 1)) neighbors.emplace_back(x, y + 1);
    int s = size;
    if (up) {
        if (x == ((size - 1) / 2) - 1)
        {
            if (isValid(x + 1, y)) neighbors.emplace_back(x + 1, y);
        }
        else if (x<((size-2)/2))
        {
            if (isValid(x + 1, y+1)) neighbors.emplace_back(x + 1, y+1); 
        }
        else if (x > ((size - 2) / 2))
        {
            if (isValid(x + 1, y-1)) neighbors.emplace_back(x + 1, y - 1);
        }
                
    }
    else {
        if (x == ((size - 1) / 2))
        {
            if (isValid(x - 1, y)) neighbors.emplace_back(x - 1, y);
        }
        else if (x <= ((size - 2) / 2))
        {
            if (isValid(x - 1, y-1)) neighbors.emplace_back(x - 1, y - 1);
        }
        else if(x > ((size - 2) / 2))
        {
            if (isValid(x - 1, y+1)) neighbors.emplace_back(x - 1, y + 1);
        }

    }

    return neighbors;
}
int HexPuzzle::getSize() const 
{
    return size;
}
