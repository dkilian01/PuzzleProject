#include "Player.h"
#include <iostream>
#include <algorithm>
#include<sstream>
#include <tuple>
Player::Player(string name):scores()
{
	this->name = name;
    scores.clear();
    loadFromFile();
}
Player::~Player()
{

}
void Player::setScore(double time, int size, const string& boardType)
{
    scores.emplace_back(time, size, boardType);
}
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
void Player::saveToFile()
{
    ofstream file(name + "_scores.txt",ios::out);
    for (const auto& score : scores) {
        file << get<0>(score) << " " << get<1>(score) << " " << get<2>(score) << "\n";
    }

    file.close();
}
void Player::loadFromFile()
{
    ifstream file(name + "_scores.txt");
    if (!file) return; // Jeœli plik nie istnieje, nie wczytujemy niczego

    scores.clear();
    double time;
    int size;
    string type;
    while (file >> time >> size>>type) {
        scores.push_back({ time, size,type });
    }

    file.close();
}

double Player::getAverageTime() const {
    if (scores.empty()) return 0.0;
    double sum = 0;
    for (const auto& s : scores) sum += get<0>(s);
    return sum / scores.size();
}

int Player::getGamesPlayed() const {
    return scores.size();
}

double Player::getBestTime() const {
    if (scores.empty()) return 0.0;
    double best = get<0>(scores[0]);
    for (const auto& s : scores) {
        if (get<0>(s) < best)
            best = get<0>(s);
    }
    return best;
}

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