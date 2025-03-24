#pragma once
#include <vector>
#include <string>
#include <fstream> 
#include <QDir>
using namespace std;
class Player
{
private:
	vector<pair<double,int>> scores;
	string name;
public:
	Player(string name);
	~Player();
	void setScore(double time, int size);
	vector<pair<double, int>> getScores();
	string getPlayerName() const;
	void setPlayerName(string name);
	void saveToFile();
	void loadFromFile();

	double getAverageTime() const;
	int getGamesPlayed() const;
	double getBestTime() const;

	static vector<Player> loadAllPlayers();
};

