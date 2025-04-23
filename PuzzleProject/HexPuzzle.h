/**
 * @file HexPuzzle.h
 * @brief Klasa reprezentuj¹ca heksagonaln¹ planszê gry puzzle z trójk¹tnymi kafelkami.
 *
 * Dziedziczy po klasie PuzzleBase i implementuje nietypow¹ planszê opart¹ na uk³adzie
 * trójk¹tów u³o¿onych na siatce heksagonalnej. Obs³uguje dwa puste pola oraz regu³y
 * przesuwania kafelków zgodnie z s¹siedztwem i kierunkiem trójk¹ta.
 */
#pragma once
#include "PuzzleBase.h"
#include "GameStateManager.h"
#include <vector>
#include <chrono>
using namespace std;

/**
 * @class HexPuzzle
 * @brief Implementacja heksagonalnej uk³adanki z trójk¹tnymi kafelkami.
 */
class HexPuzzle : public PuzzleBase {
private:
    vector<vector<int>> board;
    GameStateManager<vector<vector<int>>> stateManager;
    pair<int, int> empty1, empty2;
    int size;
    int tileAmount;
    
    chrono::time_point<chrono::steady_clock> startTime;

    bool isUpTriangle(int i, int j) const;
    bool isValid(int i, int j) const;
    pair<int, int> indexToCoord(int index) const;
   

public:
    /**
     * @brief Konstruktor planszy heksagonalnej.
     * @param size Rozmiar planszy (nieparzysta liczba > 3).
     */
    HexPuzzle(int size);

    /**
     * @brief Próbuje wykonaæ ruch przesuwaj¹c kafelek w miejsce pustego pola.
     * @param index Indeks klikniêtego pola.
     */
    void move(int index) override;

    /**
     * @brief Sprawdza, czy plansza zosta³a rozwi¹zana.
     * @retval true U³o¿ona.
     * @retval false Nieukoñczona.
     */
    bool isSolved() override;

    /**
     * @brief Zwraca aktualny stan planszy jako wektor 2D.
     */
    vector<vector<int>> getBoard() const override { return board; }

    /**
     * @brief Tasuje planszê i ustawia dwa puste pola s¹siaduj¹co.
     */
    void changeBoard() override;

    /** @brief Inicjuje licznik czasu gry. */
    void startTimer() override;

    /** @brief Zwraca czas trwania gry. */
    double getTime() override;

    /** @brief Czy mo¿liwe jest cofniêcie ruchu. */
    bool canUndo() const override { return stateManager.canUndo(); }

    /** @brief Czy mo¿liwe jest przywrócenie ruchu. */
    bool canRedo() const override { return stateManager.canRedo(); }

    /** @brief Cofa ostatni ruch. */
    void undoMove() override;

    /** @brief Przywraca cofniêty ruch. */
    void redoMove() override;

    /**
     * @brief Zapisuje stan planszy do pliku.
     * @param filename Œcie¿ka do pliku.
     */
    void saveState(const std::string& filename) override;

    /**
     * @brief Wczytuje stan gry z pliku.
     * @param filename Œcie¿ka do pliku.
     * @retval true Wczytano poprawnie.
     * @retval false B³¹d.
     */
    bool loadState(const std::string& filename) override;

    /** @brief Zwraca ca³kowit¹ liczbê kafelków. */
    int getTileAmount();

    /** @brief Zwraca rozmiar planszy. */
    int getSize() const override;

    /**
     * @brief Zwraca s¹siednie pola dla danego trójk¹ta.
     * @param x Wiersz.
     * @param y Kolumna.
     * @return Lista wspó³rzêdnych s¹siadów.
     */
    vector<pair<int, int>> getTriangleNeighbors(int x, int y) const;
};
