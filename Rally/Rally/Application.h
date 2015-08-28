#pragma once
#include "Globals.h"
#include "LTexture.h"
#include "Car.h"
#include "Button.h"
#include "MapGenerator.h"
#include "XmlWriter.h"
#include "PreviousGame.h"
#include "Timer.h"

class Application
{
public:
	Application();
	~Application();

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Game states;
	void gameStart(std::fstream&);
	void menu();
	void instructionsScreen();

	void drawObstaclesHelper(SDL_Renderer&, SDL_Rect*, int);
	int estimateDifficulty(int);
	void estimateStartingAngle(int);


	//Frees media and shuts down SDL

	void close(Car&);

	SDL_Texture* loadTexture(std::string path);
	void addDeposit();
	void removeDeposit();
	void makeDeposit();
	void makeBet();
	void removeBet();

	/*double getCredit();*/
	void setCredit();

	std::string timer(int);
	void loadingScreen(SDL_Renderer*, LTexture&, SDL_Color&,Car&);

	//HighScore functions
	void createBlankFile();
	bool fileExist(const char*);
	void writeLastTenGames(std::fstream&);
	std::vector<PreviousGame>readHighScores(std::fstream&);
	void lastTenGamesScreen(std::fstream&);

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


	Uint32 startTimeTemp;
	int timeTemp;
	
	int screenFPS;

	double estimatedPlayerWin;
	double startingAngle;

	//XML tags
	std::string startGame;
	std::string endGame;
	XmlWriter obj;

	MapGenerator map;

	Mix_Music* menuBackgroundSound;
	Mix_Chunk* beep;
	Mix_Chunk* go;

	int startingGameTimer;
	int time;
	int realTime;
	double startCredit;
	double playerBet;
	double playerWin = 0;
	double coef;
	int deposit;
};


