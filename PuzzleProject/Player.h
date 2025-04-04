#pragma once
#include <vector>
#include <string>
#include <fstream> 
#include <QDir>
using namespace std;
class Player
{
private:
	vector<tuple<double, int, string>> scores;
	string name;
public:
	Player(string name);
	~Player();
	void setScore(double time, int size, const string& boardType);
	vector<tuple<double, int,string>> getScores() const;
	string getPlayerName() const;
	void setPlayerName(string name);
	void saveToFile();
	void loadFromFile();

	double getAverageTime() const;
	int getGamesPlayed() const;
	double getBestTime() const;

	static vector<Player> loadAllPlayers();
};

