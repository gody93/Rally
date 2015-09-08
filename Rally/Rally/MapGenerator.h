#pragma once
#include "Globals.h"
class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();
	//Sets the map
	void chooseMap();
	//Gets obstacle positions from file, depending on map chosen
	void readObstaclesFromFile(std::string);
	//Sets difficulty, time, and estimatedPlayer win
	void estimateDifficulty(int&, double&, double&, double&);
	//Sets starting angle based on map
	void estimateStartingAngle(double&);

	//Sets obstacles across the map
	void setObstacles(SDL_Rect*);
	SDL_Rect* getObstacles() const;

	void setFileName(std::string);
	std::string getFileName() const;

	void setObstacleFileName(std::string);
	std::string getObstacleFileName() const;

	void setObstaclesNumber(int);
	int getObstaclesNumber() const;

	void setDifficulty(int);
	int getDifficulty() const;

private:
	int difficultyNumber;

	std::string fileName;
	std::string obstacleFileName;
	SDL_Rect* obstacles;
	int obstaclesNumber;
};

