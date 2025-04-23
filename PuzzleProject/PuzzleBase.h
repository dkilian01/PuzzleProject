/**
 * @file PuzzleBase.h
 * @brief Abstrakcyjna klasa bazowa dla ró¿nych typów plansz gry puzzle.
 *
 * Definiuje wspólny interfejs dla klasycznych i heksagonalnych uk³adanek,
 * który musi zostaæ zaimplementowany przez klasy dziedzicz¹ce (PuzzleBoard, HexPuzzle).
 */
#pragma once
#include <vector>
#include<string>
 /**
  * @class PuzzleBase
  * @brief Bazowy interfejs dla implementacji uk³adanek.
  */
class PuzzleBase {
public:
    /**
     * @brief Wykonuje próbê przesuniêcia kafelka pod wskazanym indeksem.
     * @param index Indeks kafelka.
     */
    virtual void move(int index) = 0;

    /**
     * @brief Sprawdza, czy uk³adanka zosta³a u³o¿ona poprawnie.
     * @return true jeœli rozwi¹zana, false w przeciwnym razie.
     */
    virtual bool isSolved() = 0;

    /**
     * @brief Zwraca aktualny stan planszy.
     * @return Plansza jako wektor 2D wartoœci.
     */
    virtual std::vector<std::vector<int>> getBoard() const = 0;

    /** @brief Rozpoczyna pomiar czasu gry. */
    virtual void startTimer() = 0;

    /** @brief Zwraca czas gry w sekundach. */
    virtual double getTime()  { return 0.0; }

    /** @brief Cofa ostatni ruch. */
    virtual void undoMove() = 0;

    /** @brief Przywraca cofniêty ruch. */
    virtual void redoMove() = 0;

    /** @brief Sprawdza, czy mo¿liwe jest cofniêcie ruchu. */
    virtual bool canUndo() const { return false; }

    /** @brief Sprawdza, czy mo¿liwe jest przywrócenie ruchu. */
    virtual bool canRedo() const { return false; }

    /** @brief Tasuje planszê (rozpoczêcie nowej gry). */
    virtual void changeBoard() = 0;

    /**
     * @brief Zapisuje stan gry do pliku.
     * @param filename Œcie¿ka pliku.
     */
    virtual void saveState(const std::string&) {}

    /**
     * @brief Wczytuje stan gry z pliku.
     * @param filename Œcie¿ka pliku.
     * @return true jeœli siê powiod³o, false w przeciwnym razie.
     */
    virtual bool loadState(const std::string&) { return false; }

    /** @brief Wirtualny destruktor. */
    virtual ~PuzzleBase() {}

    /**
     * @brief Zwraca rozmiar planszy.
     * @return Rozmiar zale¿ny od implementacji.
     */
    virtual int getSize() const = 0;
protected:
    /**< Flaga okreœlaj¹ca, czy uk³adanka zosta³a rozwi¹zana */
    bool solved = false;
    
    
};