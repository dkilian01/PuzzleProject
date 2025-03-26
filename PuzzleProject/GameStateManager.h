#pragma once
#include <vector>
#include <stack>
#include <fstream>

template <typename T>
class GameStateManager {
private:
    std::stack<T> undoStack;
    std::stack<T> redoStack;

public:
    void saveState(const T& state) {
        undoStack.push(state);
        while (!redoStack.empty()) redoStack.pop();  // Czyszczenie redo przy nowym ruchu
    }

    bool canUndo() const { return !undoStack.empty(); }
    bool canRedo() const { return !redoStack.empty(); }

    T undo(T currentState) {
        if (!canUndo()) return currentState;
        redoStack.push(currentState);
        T previousState = undoStack.top();
        undoStack.pop();
        return previousState;
    }

    T redo(T currentState) {
        if (!canRedo()) return currentState;
        undoStack.push(currentState);
        T nextState = redoStack.top();
        redoStack.pop();
        return nextState;
    }

    void saveToFile(const std::string& filename, const T& state) {
        std::ofstream out(filename);
        for (const auto& row : state) {
            for (int v : row) out << v << " ";
            out << "\n";
        }
        out.close();
    }

    bool loadFromFile(const std::string& filename, T& state) {
        std::ifstream in(filename);
        if (!in) return false;
        for (auto& row : state)
            for (int& v : row) in >> v;
        in.close();
        return true;
    }
};
