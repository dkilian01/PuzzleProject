#include "Player.h"
#include <iostream>
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
string Player::getPlayerName()
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