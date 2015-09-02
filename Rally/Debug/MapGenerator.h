#pragma once
#include "Globals.h"
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();

	void chooseMap();
	void readObstaclesFromFile(std::string);
	void estimateDifficulty(int&, double&, double&, double&);
	void estimateStartingAngle(double&);

	void setObstacles(SDL_Rect*);
	SDL_Rect* getObstacles() const;

	void setFileName(std::string);
	std::string getFileName() const;

	void setObstacleFileName(std::string);
	std::string getObstacleFileName() const;

	void setObstaclesNumber(int);
	int getObstaclesNumber() const;

private:
	int difficultyNumber;

	std::string fileName;
	std::string obstacleFileName;
	SDL_Rect* obstacles;
	int obstaclesNumber;
};

