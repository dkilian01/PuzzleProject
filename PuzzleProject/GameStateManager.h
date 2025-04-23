/**
 * @file GameStateManager.h
 * @brief Szablonowa klasa zarz¹dzaj¹ca histori¹ stanu gry (undo/redo).
 *
 * Przechowuje historiê zmian w stanie gry przy pomocy dwóch stosów:
 * - undoStack: do cofania ruchów,
 * - redoStack: do przywracania cofniêtych kroków.
 *
 * Obs³uguje równie¿ zapis i odczyt stanu do/z pliku (wraz z czasem).
 */
#pragma once
#include <vector>
#include <stack>
#include <fstream>
 /**
  * @class GameStateManager
  * @brief Zarz¹dza histori¹ zmian stanu gry (undo/redo) oraz zapisem do pliku.
  *
  * @tparam T Typ reprezentuj¹cy stan gry (np. vector<vector<int>>).
  */
template <typename T>
class GameStateManager {
private:
    std::stack<T> undoStack;
    std::stack<T> redoStack;

public:
    /**
     * @brief Zapisuje nowy stan do stosu undo i czyœci redo.
     * @param state Nowy stan do zapisania.
     */
    void saveState(const T& state) {
        undoStack.push(state);
        while (!redoStack.empty()) redoStack.pop();  // Czyszczenie redo przy nowym ruchu
    }

    /**
     * @brief Sprawdza mo¿liwoœæ cofniêcia ruchu.
     * @retval true Jeœli stos undo nie jest pusty.
     * @retval false W przeciwnym razie.
     */
    bool canUndo() const { return !undoStack.empty(); }

    /**
     * @brief Sprawdza mo¿liwoœæ przywrócenia ruchu.
     * @retval true Jeœli stos redo nie jest pusty.
     * @retval false W przeciwnym razie.
     */
    bool canRedo() const { return !redoStack.empty(); }

    /**
     * @brief Cofa do poprzedniego stanu gry.
     * @param currentState Aktualny stan do zapisania w redo.
     * @return Poprzedni stan.
     */
    T undo(T currentState) {
        if (!canUndo()) return currentState;
        redoStack.push(currentState);
        T previousState = undoStack.top();
        undoStack.pop();
        return previousState;
    }

    /**
     * @brief Przywraca stan gry cofniêty wczeœniej.
     * @param currentState Aktualny stan do zapisania w undo.
     * @return Przywrócony stan.
     */
    T redo(T currentState) {
        if (!canRedo()) return currentState;
        undoStack.push(currentState);
        T nextState = redoStack.top();
        redoStack.pop();
        return nextState;
    }

    /**
     * @brief Zapisuje stan gry wraz z czasem do pliku tekstowego.
     * @param filename Œcie¿ka pliku.
     * @param state Aktualny stan planszy.
     * @param time Czas gry w sekundach.
     */
    void saveToFile(const std::string& filename, const T& state,double time) {
        std::ofstream out(filename);
        out << time << "\n";
        for (const auto& row : state) {
            for (int v : row) out << v << " ";
            out << "\n";
        }
        out.close();
    }

    /**
     * @brief Wczytuje stan gry i czas z pliku.
     * @param filename Œcie¿ka pliku.
     * @param state Zmienna, do której zostanie wczytany stan.
     * @param time Zmienna, do której zostanie wczytany czas.
     * @retval true Wczytano poprawnie.
     * @retval false Plik nie istnieje lub b³¹d formatu.
     */
    bool loadFromFile(const std::string& filename, T& state,double& time) {
        std::ifstream in(filename);
        if (!in) return false;
        in >> time;
        for (auto& row : state)
            for (int& v : row) in >> v;
        in.close();
        return true;
    }
};
