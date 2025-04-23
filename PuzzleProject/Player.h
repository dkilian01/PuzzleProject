/**
 * @file Player.h
 * @brief Klasa reprezentuj¹ca gracza i jego statystyki w grze puzzle.
 *
 * Klasa obs³uguje nazwê gracza, zapis i wczytywanie wyników z pliku,
 * oraz metody analizy danych jak œredni czas gry, liczba rozegranych gier,
 * najlepszy wynik oraz globalne wczytywanie wszystkich graczy.
 */
#pragma once
#include <vector>
#include <string>
#include <fstream> 
#include <QDir>
using namespace std;
/**
 * @class Player
 * @brief Klasa modeluj¹ca gracza wraz z jego wynikami w ró¿nych grach.
 */
class Player
{
private:
	vector<tuple<double, int, string>> scores;
	string name;
public:
	/**
	 * @brief Konstruktor inicjalizuj¹cy gracza i wczytuj¹cy jego wyniki z pliku.
	 * @param name Nazwa gracza.
	 */
	Player(string name);

	/** @brief Destruktor klasy. */
	~Player();

	/**
	 * @brief Dodaje nowy wynik gracza.
	 * @param time Czas gry.
	 * @param size Rozmiar planszy.
	 * @param boardType Typ planszy ("classic", "hex").
	 */
	void setScore(double time, int size, const string& boardType);

	/**
	 * @brief Zwraca listê wyników gracza.
	 * @return Wektor krotek (czas, rozmiar, typ).
	 */
	vector<tuple<double, int,string>> getScores() const;

	/** @brief Zwraca nazwê gracza. */
	string getPlayerName() const;

	/**
	 * @brief Ustawia now¹ nazwê gracza.
	 * @param name Nowa nazwa.
	 */
	void setPlayerName(string name);

	/** @brief Zapisuje wyniki gracza do pliku. */
	void saveToFile();

	/** @brief Wczytuje wyniki gracza z pliku. */
	void loadFromFile();

	/**
	 * @brief Zwraca œredni czas gry gracza.
	 * @return Œrednia z wszystkich czasów.
	 */
	double getAverageTime() const;

	/**
	 * @brief Zwraca liczbê rozegranych gier.
	 * @return Iloœæ wyników zapisanych w historii.
	 */
	int getGamesPlayed() const;

	/**
	 * @brief Zwraca najlepszy (najkrótszy) czas gry gracza.
	 * @return Najlepszy czas w sekundach.
	 */
	double getBestTime() const;

	/**
	 * @brief Wczytuje dane wszystkich graczy z plików *_scores.txt.
	 * @return Wektor obiektów graczy.
	 */
	static vector<Player> loadAllPlayers();
};

