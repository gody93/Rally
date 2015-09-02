#pragma once
#include "Globals.h"

class MoneyManager
{
public:
	MoneyManager();
	~MoneyManager();

	void addDeposit(int&);
	void removeDeposit(int&);
	void makeDeposit(double&, int&);
	void makeBet(double&, double&);
	void removeBet(double&);
	void setCredit(double&);
};

