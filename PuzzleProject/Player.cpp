#include "Player.h"
#include <iostream>
#include <algorithm>
#include<sstream>
#include <tuple>
// Konstruktor klasy Player – przyjmuje nazwê gracza i od razu próbuje wczytaæ jego wyniki z pliku
Player::Player(string name):scores()
{
	this->name = name;
    scores.clear();
    loadFromFile();
}
Player::~Player()
{

}
// Dodaje nowy wynik gracza (czas gry, rozmiar planszy, typ planszy)
void Player::setScore(double time, int size, const string& boardType)
{
    scores.emplace_back(time, size, boardType);
}
// Zwraca wszystkie zapisane wyniki gracza jako wektor krotek
vector<tuple<double, int,string>> Player::getScores() const{
	return scores;
}
void Player::setPlayerName(string name)
{
	this->name = name;
}
string Player::getPlayerName() const
{
	return name;
}
// Zapisuje wyniki gracza do pliku o nazwie "<nazwa_gracza>_scores.txt"
void Player::saveToFile()
{
    ofstream file(name + "_scores.txt",ios::out); // Otwiera plik w trybie nadpisywania
    for (const auto& score : scores) {
        // Zapisuje dane w formacie: <czas> <rozmiar> <typ>
        file << get<0>(score) << " " << get<1>(score) << " " << get<2>(score) << "\n";
    }

    file.close();
}
//Wczytywanie
void Player::loadFromFile()
{
    ifstream file(name + "_scores.txt");
    if (!file) return; // Jeœli plik nie istnieje, nie wczytujemy niczego

    scores.clear();// Czyœci istniej¹ce dane przed wczytaniem

    double time;
    int size;
    string type;
    while (file >> time >> size>>type) {
        scores.push_back({ time, size,type });
    }

    file.close();
}
// Zwraca œredni czas gry dla gracza (jeœli brak wyników, zwraca 0.0)
double Player::getAverageTime() const {
    if (scores.empty()) return 0.0;
    double sum = 0;
    for (const auto& s : scores) sum += get<0>(s);
    return sum / scores.size();
}
// Zwraca liczbê rozegranych gier (czyli d³ugoœæ wektora wyników)
int Player::getGamesPlayed() const {
    return scores.size();
}
// Zwraca najlepszy czas gracza (najni¿szy spoœród zapisanych)
double Player::getBestTime() const {
    if (scores.empty()) return 0.0;
    double best = get<0>(scores[0]);
    for (const auto& s : scores) {
        if (get<0>(s) < best)
            best = get<0>(s);
    }
    return best;
}
// Funkcja statyczna: wczytuje wszystkich graczy na podstawie plików *_scores.txt w bie¿¹cym katalogu
vector<Player> Player::loadAllPlayers() {
    vector<Player> players;
    QDir dir(".");
    QStringList files = dir.entryList(QStringList() << "*_scores.txt", QDir::Files);
    for (const QString& file : files) {
        string name = file.left(file.indexOf("_scores.txt")).toStdString();
        players.emplace_back(Player(name));
    }
    return players;
}