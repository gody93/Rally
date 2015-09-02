#pragma once
#include "Globals.h"
#include "PreviousGame.h"

class LastTenGames
{
public:
	LastTenGames();
	~LastTenGames();

	void createBlankFile();
	bool fileExist(const char*);
	void writeLastTenGames(std::fstream&, double&, int&, double&, double&, double&);
	std::vector<PreviousGame> readLastTenGames(std::fstream&);
};
