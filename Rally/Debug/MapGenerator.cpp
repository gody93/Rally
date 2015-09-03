#include "MapGenerator.h"

//random generator
std::random_device rd;
std::mt19937 range(rd());
std::uniform_int_distribution<int> distr(0, 8);

MapGenerator::MapGenerator()
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::readObstaclesFromFile(std::string mapName)
{
	std::fstream inFile(obstacleFileName.c_str(), std::ios::in);

	int rows;
	inFile >> rows;
	setObstaclesNumber(rows);
	SDL_Rect* wall = new SDL_Rect[rows];

	for (int i = 0; i < rows; i++)
	{
		inFile >> wall[i].x;
		inFile >> wall[i].y;
		inFile >> wall[i].w;
		inFile >> wall[i].h;
	}

	setObstacles(wall);
	inFile.close();
}

void MapGenerator::setObstacles(SDL_Rect* obstacles)
{
	this->obstacles = obstacles;
}

SDL_Rect* MapGenerator::getObstacles() const
{
	return this->obstacles;
}

void MapGenerator::chooseMap()
{
	difficultyNumber = distr(range);
	switch (difficultyNumber)
	{
	case 0: setFileName("img\\maps\\maze_easy_1.PNG"); setObstacleFileName("obstacles\\maze_easy_1_obstacles.txt"); break;
	case 1: setFileName("img\\maps\\maze_easy_2.PNG"); setObstacleFileName("obstacles\\maze_easy_2_obstacles.txt"); break;
	case 2: setFileName("img\\maps\\maze_easy_3.PNG"); setObstacleFileName("obstacles\\maze_easy_3_obstacles.txt"); break;
	case 3: setFileName("img\\maps\\maze_medium_1.PNG"); setObstacleFileName("obstacles\\maze_medium_1_obstacles.txt"); break;
	case 4: setFileName("img\\maps\\maze_medium_2.PNG"); setObstacleFileName("obstacles\\maze_medium_2_obstacles.txt"); break;
	case 5: setFileName("img\\maps\\maze_medium_3.PNG"); setObstacleFileName("obstacles\\maze_medium_3_obstacles.txt"); break;
	case 6: setFileName("img\\maps\\maze_hard_1.PNG"); setObstacleFileName("obstacles\\maze_hard_1_obstacles.txt"); break;
	case 7: setFileName("img\\maps\\maze_hard_2.PNG"); setObstacleFileName("obstacles\\maze_hard_2_obstacles.txt"); break;
	case 8: setFileName("img\\maps\\maze_hard_3.PNG"); setObstacleFileName("obstacles\\maze_hard_3_obstacles.txt"); break;
	default:
		break;
	}
}

void MapGenerator::estimateDifficulty(int& time, double& coef, double& playerBet, double& estimatedPlayerWin)
{
	//there are 3 levels for every difficulty
	switch (difficultyNumber / 3)
	{
	case 0: //easy
		time = 17;
		coef = 0.2;
		estimatedPlayerWin = playerBet * coef;
		break;
	case 1: //medium
		time = 19;
		coef = 0.5;
		estimatedPlayerWin = playerBet * coef;
		break;
	case 2: //hard
		time = 21;
		coef = 0.8;
		estimatedPlayerWin = playerBet * coef;
		break;
	default:
		break;
	}
}

void MapGenerator::estimateStartingAngle(double& startingAngle)
{
	//there are 3 levels for every difficulty
	switch (difficultyNumber)
	{
	case 0: startingAngle = 0; break;
	case 1: startingAngle = 270; break;
	case 2: startingAngle = 270; break;
	case 3: startingAngle = 0; break;
	case 4: startingAngle = 270; break;
	case 5: startingAngle = 270; break;
	case 6: startingAngle = 0; break;
	case 7: startingAngle = 270; break;
	case 8: startingAngle = 270; break;
	}
}

void MapGenerator::setFileName(std::string fileName)
{
	this->fileName = fileName;
}

std::string MapGenerator::getFileName() const
{
	return this->fileName;
}

void MapGenerator::setObstacleFileName(std::string obstacleFileName)
{
	this->obstacleFileName = obstacleFileName;
}

std::string MapGenerator::getObstacleFileName() const
{
	return this->obstacleFileName;
}

void MapGenerator::setObstaclesNumber(int obstaclesNumber)
{
	this->obstaclesNumber = obstaclesNumber;
}

int MapGenerator::getObstaclesNumber() const
{
	return this->obstaclesNumber;
}

void MapGenerator::setDifficulty(int difficultyNumber)
{
	this->difficultyNumber = difficultyNumber;
}

int MapGenerator::getDifficulty() const
{
	return this->difficultyNumber;
}