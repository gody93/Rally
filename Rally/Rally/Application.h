#pragma once
#include "Globals.h"
#include "Car.h"
#include "Button.h"
#include "MapGenerator.h"
#include "XmlWriter.h"
#include "LastTenGames.h"
#include "Timer.h"
#include "MoneyManager.h"
#include "RallyInfo.h"

class Application
{
public:
	Application();
	~Application();

	//Frees media and shuts down SDL
	void close();

	//Displays the menu of the game
	void menu();


private:
	//composition
	XmlWriter obj;
	MapGenerator map;
	MoneyManager moneyManager;
	LastTenGames lastTenGamesManager;
	RallyInfo gameData;
	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia(int);

	//Displays the actual game with car handling
	void gameStart(std::fstream&, int&);

	void caseYouWin(std::fstream&);
	void caseYouLose(std::fstream&);

	//Does a countdown before the start of the race
	void loadingScreen(SDL_Renderer*, LTexture&, SDL_Color&, Car&);

	//Displays rules and how to play instructions
	void instructionsScreen();

	//Displays last ten games on screen
	void lastTenGamesScreen(std::fstream&);

	//User chooses preferred car
	int chooseCar(SDL_Renderer*);

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

	//Button background loading
	void loadButtonMedia();

	//Frees button pointers
	void freeButtonPointers();

	//Loads menu text
	void loadText();

	//Frees text pointers
	void freeTextPointers();

	//Creates blinking effect
	void blinkingEffect(int&);

	//Checks if music is on in game
	void checkMusicInGame(Car&, SDL_Event&);

	//Checks if music is on
	void checkMusic();

	//Renders menu background textures
	void renderMenuTextures();

	//Renders on/off music texture
	void renderMusicButton();

	//Scene textures
	LTexture gCarTexture, gFirstCarTexture, gSecondCarTexture, gThirdCarTexture;
	LTexture gBackgroundTexture;
	LTexture gSpeedMeter;
	SDL_Rect gSpeedMeterClips[46];
	LTexture youLose;
	LTexture youWin;

	//menu sounds
	Mix_Music* menuBackgroundSound;
	Mix_Chunk* beep;
	Mix_Chunk* go;

	int buttonWidth = 160;
	int	buttonHeight = 50;

	//Menu Button Pointers
	Button* exitButton = new Button(buttonWidth, buttonHeight, 370, 600);
	Button* startButton = new Button(buttonWidth, buttonHeight, 370, 200);
	Button* instructionsButton = new Button(buttonWidth, buttonHeight, 650, 370);
	Button* addDepositButton = new Button(buttonHeight, buttonHeight, 90, 135);
	Button* removeDepositButton = new Button(buttonHeight, buttonHeight, 200, 135);
	Button* makeDepositButton = new Button(buttonWidth, buttonHeight, 77, 180);
	Button* addBetButton = new Button(buttonHeight, buttonHeight, 665, 135);
	Button* removeBetButton = new Button(buttonHeight, buttonHeight, 775, 135);
	Button* betButton = new Button(buttonWidth, buttonHeight, 650, 180);
	Button* lastTenGamesButton = new Button(250, buttonHeight, 72, 370);
	Button* onMusicButton = new Button(45, buttonHeight, 830, 10);
	Button* offMusicButton = new Button(45, buttonHeight, 830, 10);

	//Menu Texture Pointers
	LTexture* menuTitle = new LTexture();
	LTexture* exitButtonText = new LTexture();
	LTexture* startButtonText = new LTexture();
	LTexture* instructionText = new LTexture();
	LTexture* creditText = new LTexture();
	LTexture* creditNumber = new LTexture();
	LTexture* depositNum = new LTexture();
	LTexture* makeDepositText = new LTexture();
	LTexture* betNum = new LTexture();
	LTexture* betText = new LTexture();
	LTexture* highScoresText = new LTexture();
	LTexture* insertCreditText = new LTexture();
	LTexture* insertCreditTextTwo = new LTexture();
	LTexture* insertCreditTextThree = new LTexture();
	LTexture* insertCreditTextFour = new LTexture();

	enum cars { CAR_ONE = 1, CAR_TWO, CAR_THREE };
	const unsigned int ONE_SECOND = 1000;

	Uint32 startTimeTemp;
	int timeTemp;

	int screenFPS;

	bool isMusicOn;

	double estimatedPlayerWin;
	double startingAngle;
	int deposit;
};


