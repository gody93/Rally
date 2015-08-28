#pragma once
#include "Globals.h"
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	int chooseMap();

	void readObstaclesFromFile(std::string);

	void setObstacles(SDL_Rect*);
	SDL_Rect* getObstacles() const;

	void setFileName(std::string);
	std::string getFileName() const;

	void setObstacleFileName(std::string);
	std::string getObstacleFileName() const;

	void setObstaclesNumber(int);
	int getObstaclesNumber() const;

private:
	std::string fileName;
	std::string obstacleFileName;
	SDL_Rect* obstacles;
	int obstaclesNumber;
};

