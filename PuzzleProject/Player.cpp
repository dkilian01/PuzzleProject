#include "Player.h"
Player::Player(string name)
{
	this->name = name;
}
void Player::setScore(double time, int size)
{
	scores.push_back(pair(time,size));
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

}
void Player::loadFromFile()
{

}