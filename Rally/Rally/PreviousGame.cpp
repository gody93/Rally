#include "PreviousGame.h"


PreviousGame::PreviousGame(double credit, int time, double bet, double win, double difficulty)
{
	setCredit(credit);
	setTime(time);
	setPlayerBet(bet);
	setPlayerWin(win);
	setDificulty(difficulty);
}


PreviousGame::~PreviousGame()
{
}

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
void PreviousGame::setDificulty(double coef)
{
	std::string something;
	if (coef == 0.2)
	{
		something = "Easy";
	}
	else if (coef == 0.5)
	{
		something = "Medium";
	}
	else if (coef == 0.8)
	{
		something = "Hard";
	}

	const char *nameValue = something.data();
	int length = something.size();
	strncpy(this->difficulty, nameValue, length);
	this->difficulty[length] = '\0';

}

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