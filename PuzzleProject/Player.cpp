#include "Player.h"

void Player::setScore(double time, int size)
{
	scores.push_back(pair(time,size));
}
vector<pair<double, int>> Player::getScores() {
	return scores;
}
void Player::setPlayerName(string name)
{
	playerName = name;
}
string Player::getPlayerName()
{
	return playerName;
}