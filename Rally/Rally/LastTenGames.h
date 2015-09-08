#pragma once
#include "Globals.h"
#include "PreviousGame.h"

class LastTenGames
{
public:
	LastTenGames();
	~LastTenGames();

	//Creates blank file with empty default constructor,if the file doesn't exist
	void createBlankFile();
	//Checks if file exists;
	bool fileExist(const char*);
	//Moves all records one position lower, and writes latest game at top of file;
	void writeLastTenGames(std::fstream&, double, int, double, double, double);
	//Saves information from previousGames.txt in vector;
	std::vector<PreviousGame> readLastTenGames(std::fstream&);
};
