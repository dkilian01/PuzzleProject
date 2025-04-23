/**
 * @file PuzzleBoard.h
 * @brief Klasa reprezentuj¹ca klasyczn¹ planszê gry w uk³adankê.
 *
 * Dziedziczy po klasie abstrakcyjnej PuzzleBase i implementuje logikê gry
 * dla klasycznej kwadratowej planszy o rozmiarze NxN.
 */
#pragma once
#include "PuzzleBase.h"
#include "GameStateManager.h"
#include <vector>
#include <chrono>
#include <random>
#include <fstream> 
using namespace std;
/**
 * @class PuzzleBoard
 * @brief Implementacja klasycznej planszy gry puzzle.
 */
class PuzzleBoard :
    public PuzzleBase
{
private:
    vector<vector<int>> board;
    GameStateManager<vector<vector<int>>> stateManager;
    chrono::time_point<chrono::steady_clock> startTime;

public:
    /**
     * @brief Konstruktor planszy klasycznej.
     * @param size Rozmiar planszy (NxN).
     */
    PuzzleBoard(int size);

    /** @brief Wykonuje ruch kafelkiem na podstawie indeksu. */
    void move(int index) override;

    /**
     * @brief Sprawdza, czy plansza jest u³o¿ona poprawnie.
     * @retval true Plansza u³o¿ona.
     * @retval false Gra nadal trwa.
     */
    bool isSolved() override;

    /** @brief Zwraca rozmiar planszy. */
    int getSize() const override{ return board.size(); }

    /** @brief Zwraca dwuwymiarowy wektor reprezentuj¹cy stan planszy. */
    vector<vector<int>> getBoard() const override { return board; }

    /** @brief Tasuje planszê i rozpoczyna now¹ grê. */
    void changeBoard() override;

    /** @brief Inicjuje pomiar czasu gry. */
    void startTimer() override;

    /** @brief Zwraca czas gry w sekundach. */
    double getTime()  override;

    /** @brief Czy mo¿liwe jest cofniêcie ruchu. */
    bool canUndo() const override;

    /** @brief Czy mo¿liwe jest przywrócenie ruchu. */
    bool canRedo() const override;

    /** @brief Cofa ostatni ruch. */
    void undoMove() override;

    /** @brief Przywraca ruch cofniêty. */
    void redoMove() override;

    /**
     * @brief Zapisuje aktualny stan planszy do pliku.
     * @param filename Œcie¿ka do pliku.
     */
    void saveState(const string& filename) override;

    /**
     * @brief Wczytuje stan planszy z pliku.
     * @param filename Œcie¿ka do pliku.
     * @retval true Wczytano poprawnie.
     * @retval false B³¹d podczas wczytywania.
     */
    bool loadState(const string& filename) override;
    
};

