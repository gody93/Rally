#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Globals.h"
class PreviousGame
{
public:
	PreviousGame(double = 0.0, int time = 0, double bet = 0.0, double win = 0.0, double difficulty = 0.0);
	~PreviousGame();
	//Setters for private fields
	void setCredit(double credit);
	void setTime(int time);
	void setPlayerBet(double bet);
	void setPlayerWin(double win);
	void setDifficulty(double coef);
	
	//Getters for private fields
	double getCredit() const;
	int getTime() const;
	double getPlayerBet() const;
	double getPlayerWin() const;
	std::string getDifficulty() const;

private:
	double credit;
	int time;
	double playerBet;
	double playerWin;
	char difficulty[10];
};

