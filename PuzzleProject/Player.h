#pragma once
#include<vector>
#include<string>
using namespace std;
class Player
{
private:
	vector<pair<double,int>> scores;
	string playerName;
public:
	void setScore(double time, int size);
	vector<pair<double, int>> getScores();
	string getPlayerName();
	void setPlayerName(string name);
};

