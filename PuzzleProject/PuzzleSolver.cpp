#include "PuzzleSolver.h"
#include "PuzzleBoard.h"

#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <sstream>
#include <chrono>
#include <fstream> 
using namespace std;
struct PuzzleState {
    vector<vector<int>> board;
    int g; // koszt do tej pory
    int h; // heurystyka
    vector<int> path;

    bool operator>(const PuzzleState& other) const {
        return g + h > other.g + other.h;
    }
};

int PuzzleSolver::manhattan(const vector<vector<int>>& board) {
    int dist = 0;
    int size = board.size();
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            int val = board[i][j];
            if (val == size * size) continue;
            int targetX = (val - 1) / size;
            int targetY = (val - 1) % size;
            dist += abs(targetX - i) + abs(targetY - j);
        }
    return dist;
}

string PuzzleSolver::boardToString(const vector<vector<int>>& board) {
    stringstream ss;
    for (const auto& row : board)
        for (int v : row)
            ss << v << ",";
    return ss.str();
}
void logToFile(const string& message) {
    ofstream log("solver_log.txt", ios::app);
    if (log.is_open()) {
        log << message << "\n";
    }
}
vector<pair<vector<vector<int>>, int>> PuzzleSolver::getNeighbors(const vector<vector<int>>& board) {
    vector<pair<vector<vector<int>>, int>> result;
    int size = board.size();
    int x = -1, y = -1;
    int empty = size * size;

    // znajdŸ puste pole
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (board[i][j] == empty) {
                x = i; y = j;
                break;
            }

    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < size && ny < size) {
            auto newBoard = board;
            swap(newBoard[x][y], newBoard[nx][ny]);
            result.push_back({ newBoard, nx * size + ny });
        }
    }

    return result;
}

bool PuzzleSolver::isSolvable(const vector<vector<int>>& board) {
    vector<int> flat;
    int size = board.size();
    int blankRowFromTop = 0;

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            int val = board[i][j];
            if (val == size * size) blankRowFromTop = i;
            flat.push_back(val);
        }

    int inversions = 0;
    for (int i = 0; i < flat.size(); ++i)
        for (int j = i + 1; j < flat.size(); ++j)
            if (flat[i] != size * size && flat[j] != size * size && flat[i] > flat[j])
                inversions++;

    int blankRowFromBottom = size - blankRowFromTop;

    logToFile("== Sprawdzanie rozwi¹zywalnoœci ==");
    logToFile("Inwersje: " + to_string(inversions));
    logToFile("Pusty wiersz (od góry): " + to_string(blankRowFromTop));
    logToFile("Pusty wiersz (od do³u): " + to_string(blankRowFromBottom));
    logToFile("Rozmiar planszy: " + to_string(size));

    if (size % 2 == 1)
        return inversions % 2 == 0;
    else
        return (inversions + blankRowFromBottom) % 2 == 1;
}


vector<int> PuzzleSolver::solve(const PuzzleBoard& puzzle) {

    logToFile("== Próba rozwi¹zania nowej planszy ==");
    const auto& startBoard = puzzle.getBoard();
    for (const auto& row : startBoard) {
        string line;
        for (int val : row) {
            line += to_string(val) + " ";
        }
        logToFile(line);
    }
    if (!isSolvable(startBoard)) {
        
        return {};
    }

    auto startTime = chrono::steady_clock::now();
    const int timeLimit = 600;
    const int maxSteps = 5000000;

    priority_queue<PuzzleState, vector<PuzzleState>, greater<>> open;
    unordered_set<string> visited;

    PuzzleState initial = { startBoard, 0, manhattan(startBoard), {} };
    open.push(initial);
    visited.insert(boardToString(startBoard));

    int steps = 0;

    while (!open.empty()) {
        auto now = chrono::steady_clock::now();
        if (steps % 1000 == 0) {
            logToFile("Krok " + to_string(steps) + ", open size: " + to_string(open.size()) +
                ", visited: " + to_string(visited.size()));
        }
        if (++steps > maxSteps ||
            chrono::duration_cast<chrono::seconds>(now - startTime).count() > timeLimit) {
            logToFile("Przekroczon");
            return {};
        }

        PuzzleState current = open.top();
        open.pop();

        if (manhattan(current.board) == 0) {
            logToFile("Puzzle rozwi¹zane! Liczba kroków: " + to_string(current.path.size()));
            return current.path;
        }

        for (auto& [neighbor, moveIndex] : getNeighbors(current.board)) {
            string key = boardToString(neighbor);
            if (visited.count(key)) continue;

            PuzzleState next = {
                neighbor,
                current.g + 1,
                manhattan(neighbor),
                current.path
            };
            next.path.push_back(moveIndex);
            open.push(next);
            visited.insert(key);
        }
    }

    return {};
}
