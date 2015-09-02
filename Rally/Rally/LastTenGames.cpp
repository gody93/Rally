#include "LastTenGames.h"

LastTenGames::LastTenGames()
{
}

LastTenGames::~LastTenGames()
{
}

bool LastTenGames::fileExist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void LastTenGames::createBlankFile()
{
	if (!fileExist("previousGames.txt"))
	{
		PreviousGame blankGame;

		std::ofstream blankFile("previousGames.txt", std::ios::out);
		if (!blankFile)
		{
			std::cerr << "File could not be opened." << std::endl;
			exit(1);
		}
		for (int i = 0; i < 10; i++)
		{
			blankFile.write(reinterpret_cast<const char*>(&blankGame), sizeof(PreviousGame));
		}
		blankFile.close();
	}
}

void LastTenGames::writeLastTenGames(std::fstream& readfile, 
	double& startCredit, int& realTime, double& playerBet, double& playerWin, double& coef)
{
	PreviousGame blankGame;
	PreviousGame currentGame(startCredit, realTime, playerBet, playerWin, coef);
	for (int i = 9; i > 0; i--)
	{
		readfile.seekg((i - 1) * sizeof(PreviousGame));
		readfile.read(reinterpret_cast<char*>(&blankGame), sizeof(PreviousGame));
		readfile.seekg(i * sizeof(PreviousGame));
		readfile.write(reinterpret_cast<const char*>(&blankGame), sizeof(PreviousGame));
	}

	readfile.seekg(0 * sizeof(PreviousGame));
	readfile.write(reinterpret_cast<const char*>(&currentGame), sizeof(PreviousGame));
}

std::vector<PreviousGame> LastTenGames::readLastTenGames(std::fstream& fileToRead)
{
	PreviousGame tempGame;
	std::vector<PreviousGame> lastTenGames;

	for (int i = 0; i < 10; i++)
	{
		fileToRead.seekg(i*sizeof(PreviousGame));
		fileToRead.read(reinterpret_cast<char*>(&tempGame), sizeof(PreviousGame));
		lastTenGames.push_back(tempGame);
	}
	return lastTenGames;
}