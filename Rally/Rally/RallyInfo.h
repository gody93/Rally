#pragma once
#include "Globals.h"

class RallyInfo
{
public:
	RallyInfo();
	RallyInfo(std::string, std::string, int, int, double, double, double, double);
	~RallyInfo();

	void printInfo();

	void setStartGame(std::string);
	std::string getStartGame() const;

	void setEndGame(std::string);
	std::string getEndGame() const;

	void setTime(int);
	int getTime() const;

	void setRealTime(int);
	int getRealTime() const;

	void setStartCredit(double);
	double getStartCredit() const;

	void setPlayerBet(double);
	double getPlayerBet() const;

	void setPlayerWin(double);
	double getPlayerWin() const;

	void setCoef(double);
	double getCoef() const;

private:
	std::string startGame;
	std::string endGame;
	int time;
	int realTime;
	double startCredit;
	double playerBet;
	double playerWin;
	double coef;
};
