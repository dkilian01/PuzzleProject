#include "Player.h"
#include <iostream>
#include <algorithm>
#include<sstream>
Player::Player(string name):scores()
{
	this->name = name;
    scores.clear();
    loadFromFile();
}
Player::~Player()
{

}
void Player::setScore(double time, int size)
{
    scores.push_back({ time,size });
}
vector<pair<double, int>> Player::getScores() {
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
        file << score.first << " " << score.second << endl;
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

    while (file >> time >> size) {
        scores.push_back({ time, size });
    }

    file.close();
}

double Player::getAverageTime() const {
    if (scores.empty()) return 0.0;
    double sum = 0;
    for (const auto& s : scores) sum += s.first;
    return sum / scores.size();
}

int Player::getGamesPlayed() const {
    return scores.size();
}

double Player::getBestTime() const {
    if (scores.empty()) return 0.0;
    double best = scores[0].first;
    for (const auto& s : scores) {
        if (s.first < best)
            best = s.first;
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