#include "PreviousGame.h"


PreviousGame::PreviousGame(double credit, int time, double bet, double win, double difficulty)
{
	setCredit(credit);
	setTime(time);
	setPlayerBet(bet);
	setPlayerWin(win);
	setDifficulty(difficulty);
}


PreviousGame::~PreviousGame()
{
}

//Setters for private fields
void PreviousGame::setCredit(double credit)
{
	this->credit = credit;
}
void PreviousGame::setTime(int time)
{
	this->time = time;
}
void PreviousGame::setPlayerBet(double bet)
{
	this->playerBet = bet;
}
void PreviousGame::setPlayerWin(double win)
{
	this->playerWin = win;
}
void PreviousGame::setDifficulty(double coef)
{
	//Converts difficulty string to char array because of random-access file writing 
	std::string difficulty;
	if (coef == 0.2)
	{
		difficulty = "Easy";
	}
	else if (coef == 0.5)
	{
		difficulty = "Medium";
	}
	else if (coef == 0.8)
	{
		difficulty = "Hard";
	}

	const char *nameValue = difficulty.data();
	int length = difficulty.size();
	strncpy(this->difficulty, nameValue, length);
	this->difficulty[length] = '\0';

}

//Getters for private fields
double PreviousGame::getCredit() const
{
	return this->credit;
}
int PreviousGame::getTime() const
{
	return this->time;
}
double PreviousGame::getPlayerBet() const
{
	return this->playerBet;
}
double PreviousGame::getPlayerWin() const
{
	return this->playerWin;
}
std::string PreviousGame::getDifficulty() const
{
	return this->difficulty;
}