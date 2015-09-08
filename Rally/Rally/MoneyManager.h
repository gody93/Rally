#pragma once
#include "Globals.h"

class MoneyManager
{
public:
	MoneyManager();
	~MoneyManager();

	//Adds 10 to current deposit
	void addDeposit(int&);
	//Removes 10 from current deposit
	void removeDeposit(int&);
	//Adds current deposit to playerCredit
	void makeDeposit(double&, int&);
	//Adds 5 to current bet
	void makeBet(double, double&);
	//Removes 5 from current bet
	void removeBet(double&);
	//Writes the current credit into a file
	void setCredit(double);
};

