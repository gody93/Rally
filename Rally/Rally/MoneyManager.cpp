#include "MoneyManager.h"

MoneyManager::MoneyManager()
{
}

MoneyManager::~MoneyManager()
{
}

//Adds 10 to current deposit
void MoneyManager::addDeposit(int& deposit)
{
	if (deposit < 100)
	{

		deposit += 10;
	}
}

//Removes 10 from current deposit
void MoneyManager::removeDeposit(int& deposit)
{
	if (deposit > 0)
	{
		deposit -= 10;
	}
}

//Adds current deposit to playerCredit
void MoneyManager::makeDeposit(double& startCredit, int& deposit)
{
	startCredit += deposit;
	deposit = 0;
	setCredit(startCredit);
}

//Adds 5 to current bet
void MoneyManager::makeBet(double startCredit, double& playerBet)
{
	int difference = (int)(startCredit) % 10;
	if (playerBet < (int)startCredit  && playerBet < 100)
	{
		if ((playerBet + difference) < (int)startCredit)
		{
			playerBet += 5;
		}
		else
		{
			playerBet += difference;
		}
	}
}

//Removes 5 from current bet
void MoneyManager::removeBet(double& playerBet)
{
	int difference = (int)(playerBet) % 10;
	if (playerBet - 5 < 0)
	{
		playerBet -= difference;
	}
	else
	{
		playerBet -= 5;
	}
}

//Writes the current credit into a file

void MoneyManager::setCredit(double startCredit)
{
	std::ofstream file("credit.txt", std::ios::out);

	file << startCredit;

	file.close();
}