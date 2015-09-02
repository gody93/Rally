#pragma once
#include "Globals.h"
#include "LTexture.h"
#include "Car.h"
#include "Button.h"
#include "MapGenerator.h"
#include "XmlWriter.h"
#include "LastTenGames.h"
#include "Timer.h"
#include "MoneyManager.h"

class Application
{
public:
	Application();
	~Application();

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//Game states;
	void menu();
	void gameStart(std::fstream&, Button&, Button&);
	void loadingScreen(SDL_Renderer*, LTexture&, SDL_Color&, Car&, Button&);
	void instructionsScreen(Button&, Button&);
	void lastTenGamesScreen(std::fstream&, Button&, Button&);

	void drawObstaclesHelper(SDL_Renderer&, SDL_Rect*, int);

	SDL_Texture* loadTexture(std::string path);
	std::string timer(int);

private:
	//Screen dimension 
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer;

	//Scene textures
	LTexture gCarTexture;
	LTexture gBackgroundTexture;
	LTexture gSpeedMeter[23];

	Uint32 startTimeTemp;
	int timeTemp;
	
	int screenFPS;

	bool isMusicOn;

	double estimatedPlayerWin;
	double startingAngle;

	//composition
	XmlWriter obj;
	MapGenerator map;
	MoneyManager moneyManager;
	LastTenGames lastTenGamesManager;

	//menu sounds
	Mix_Music* menuBackgroundSound;
	Mix_Chunk* beep;
	Mix_Chunk* go;

	//XML tags
	std::string startGame;
	std::string endGame;
	int startingGameTimer;
	int time;
	int realTime;
	double startCredit;
	double playerBet;
	double playerWin = 0;
	double coef;
	int deposit;
};


