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
	bool loadMedia(int);

	//Frees media and shuts down SDL
	void close();

	//Menu state
	void menu();
	

private:

	//Game states
	void gameStart(std::fstream&, int&, Button&, Button&);
	void loadingScreen(SDL_Renderer*, LTexture&, SDL_Color&, Car&, Button&);
	void instructionsScreen(Button&, Button&);
	void lastTenGamesScreen(std::fstream&, Button&, Button&);
	
	int chooseCar(SDL_Renderer*, Button&, Button&);

	//Visualize obstacles
	void drawObstaclesHelper(SDL_Renderer&, SDL_Rect*, int);
	
	//Time texture in-game
	std::string timer(int);

	//Screen dimension 
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer;

	//Scene textures
	LTexture gCarTexture, gFirstCarTexture, gSecondCarTexture, gThirdCarTexture;
	LTexture gBackgroundTexture;
	LTexture gSpeedMeter;
	SDL_Rect gSpeedMeterClips[46];
	LTexture youLose;
	LTexture youWin;

	enum cars { carOne = 1, carTwo, carThree };

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


