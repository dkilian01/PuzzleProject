/**
 * @file GameLogic.h
 * @brief Klasa zarz¹dzaj¹ca logik¹ gry puzzle.
 *
 * Klasa ta odpowiada za obs³ugê planszy gry, gracza, cofania i przywracania ruchów,
 * zarz¹dzanie zapisem i wczytywaniem stanu gry oraz uruchamianie algorytmu rozwi¹zuj¹cego.
 * Przeznaczona jest do u¿ycia z zewnêtrznym interfejsem u¿ytkownika (GUI/konsolowym).
 */
#pragma once
#include "PuzzleBase.h"
#include "Player.h"
#include <memory>
#include <vector>
#include <string>
 /**
  * @class GameLogic
  * @brief Logika gry oddzielona od GUI.
  */
class GameLogic {
private:
    unique_ptr<PuzzleBase> board;
    Player player;
    string boardType;
    string saveFileName() const;
public:
    /**
     * @name Konstrukcja i inicjalizacja
     * @{
     */

    /**
     * @brief Konstruktor klasy logiki gry.
     * @param board WskaŸnik na obiekt planszy (dziedziczy po PuzzleBase).
     * @param player Gracz, którego wyniki bêd¹ rejestrowane i filtrowane.
     */
    GameLogic(unique_ptr<PuzzleBase> board, Player player);
    /** @} */

    /**
     * @name Sterowanie stanem gry
     * @{
     */

    /** @brief Rozpoczyna licznik czasu gry. */
    void start();

    /** @brief Tasuje planszê i resetuje licznik czasu. */
    void reset();

    /**
     * @brief Wykonuje ruch w planszy na podstawie indeksu kafelka.
     * @param index Indeks klikniêtego kafelka.
     */
    void move(int index);

    /**
     * @brief Sprawdza, czy gra zosta³a ukoñczona.
     * @retval true Uk³adanka zosta³a poprawnie u³o¿ona.
     * @retval false Gra trwa dalej.
     */
    bool isSolved() const;

    /**
     * @brief Zwraca czas trwania aktualnej gry.
     * @return Czas w sekundach.
     */
    double getTime() const;

    /** @} */

    /**
     * @name Operacje cofania i przywracania
     * @{
     */

    /** @brief Sprawdza mo¿liwoœæ cofniêcia ruchu. */
    bool canUndo() const;

    /** @brief Sprawdza mo¿liwoœæ przywrócenia ruchu. */
    bool canRedo() const;

    /** @brief Cofa jeden krok w historii ruchów. */
    void undo();

    /** @brief Przywraca jeden krok do przodu. */
    void redo();

    /** @} */

    /**
     * @name Zarz¹dzanie stanem gry
     * @{
     */

    /** @brief Zapisuje stan gry do pliku. */
    void saveState();

    /**
     * @brief Wczytuje stan gry z pliku (zgodnego z typem planszy).
     * @retval true Wczytano stan poprawnie.
     * @retval false Nie uda³o siê wczytaæ.
     */
    bool loadState();

    /** @} */

    /**
     * @name Dostêp do planszy
     * @{
     */

    /**
     * @brief Pobiera aktualn¹ planszê gry.
     * @return Dwuwymiarowy wektor reprezentuj¹cy planszê.
     */
    vector<vector<int>> getBoard() const;

    /**
     * @brief Pobiera rozmiar planszy.
     * @return Dla klasycznej: rozmiar krawêdzi, dla heksagonalnej: wartoœæ u¿ytkowa.
     */
    int getSize() const;

    /**
     * @brief Zwraca typ planszy.
     * @return "classic" lub "hex"
     */
    string getBoardType() const;

    /** @brief Zwraca maksymaln¹ wartoœæ na planszy. */
    int getMaxTileValue() const;

    /** @} */

    /**
     * @name Gracz i jego wyniki
     * @{
     */

     /** @brief Zwraca referencjê do gracza. */
    Player& getPlayer();

    /** @brief Zwraca nazwê gracza. */
    string getPlayerName() const;

    /**
     * @brief Zapisuje wynik gracza po ukoñczeniu gry.
     * @param time Czas gry w sekundach.
     */
    void recordWin(double time);

    /** @brief Zapisuje dane gracza do pliku. */
    void persist();



};
