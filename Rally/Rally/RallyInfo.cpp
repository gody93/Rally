#include "RallyInfo.h"

void RallyInfo::printInfo()
{
	std::cout << this->getStartGame() << std::endl;
	std::cout << this->getEndGame() << std::endl;
	std::cout << this->getTime() << std::endl;
	std::cout << this->getRealTime() << std::endl;
	std::cout << this->getStartCredit() << std::endl;
	std::cout << this->getPlayerBet() << std::endl;
	std::cout << this->getPlayerWin() << std::endl;
	std::cout << this->getCoef() << std::endl;
}

RallyInfo::RallyInfo()
{
}

RallyInfo::~RallyInfo()
{
}

RallyInfo::RallyInfo(std::string startGame, std::string endGame, int time, int realTime,
	double startCredit, double playerBet, double playerWin, double coef)
{
	setStartGame(startGame);
	setEndGame(endGame);
	setTime(time);
	setRealTime(realTime);
	setStartCredit(startCredit);
	setPlayerBet(playerBet);
	setPlayerWin(playerWin);
	setCoef(coef);
}

void RallyInfo::setStartGame(std::string startGame)
{
	this->startGame = startGame;
}

std::string RallyInfo::getStartGame() const
{
	return this->startGame;
}

void RallyInfo::setEndGame(std::string endGame)
{
	this->endGame = endGame;
}

std::string RallyInfo::getEndGame() const
{
	return this->endGame;
}

void RallyInfo::setTime(int time)
{
	this->time = time;
}

int RallyInfo::getTime() const
{
	return this->time;
}

void RallyInfo::setRealTime(int realTime)
{
	this->realTime = realTime;
}

int RallyInfo::getRealTime() const
{
	return this->realTime;
}

void RallyInfo::setStartCredit(double startCredit)
{
	this->startCredit = startCredit;
}

double RallyInfo::getStartCredit() const
{
	return this->startCredit;
}

void RallyInfo::setPlayerBet(double playerBet)
{
	this->playerBet = playerBet;
}

double RallyInfo::getPlayerBet() const
{
	return this->playerBet;
}

void RallyInfo::setPlayerWin(double playerWin)
{
	this->playerWin = playerWin;
}

double RallyInfo::getPlayerWin() const
{
	return this->playerWin;
}

void RallyInfo::setCoef(double coef)
{
	this->coef = coef;
}

double RallyInfo::getCoef() const
{
	return this->coef;
}