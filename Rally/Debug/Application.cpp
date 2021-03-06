#include "Application.h"

Application::Application() : SCREEN_WIDTH(920), SCREEN_HEIGHT(665), gWindow(NULL), gRenderer(NULL), startingAngle(0), screenFPS(24)
{
}

Application::~Application()
{
	close();
}

bool Application::init()
{
	//Initialization flag
	bool success = true;

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	int result = 0;
	int flags = MIX_INIT_MP3;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Rally", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				if (flags != (result = Mix_Init(flags))) {
					printf("Could not initialize mixer (result: %d).\n", result);
					printf("Mix_Init: %s\n", Mix_GetError());
					exit(1);
				}
			}
		}
	}

	return success;
}

bool Application::loadMedia(int car)
{
	//Loading success flag
	bool success = true;

	map.chooseMap();
	map.estimateDifficulty(time, coef, playerBet, estimatedPlayerWin);
	map.readObstaclesFromFile(map.getFileName());

	if (!gBackgroundTexture.loadFromFile(map.getFileName(), gRenderer))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	map.estimateStartingAngle(startingAngle);

	switch (car)
	{
	case carOne:
		if (!gFirstCarTexture.loadFromFile("img/cars/carOne.png", gRenderer))
		{
			printf("Failed to load car texture!\n");
			success = false;
		}
		break;
	case carTwo:
		if (!gSecondCarTexture.loadFromFile("img/cars/carTwo.png", gRenderer))
		{
			printf("Failed to load car texture!\n");
			success = false;
		}
		break;
	case carThree:
		if (!gThirdCarTexture.loadFromFile("img/cars/carThree.png", gRenderer))
		{
			printf("Failed to load car texture!\n");
			success = false;
		}
		break;
	default:
		break;
	}

	if (!youLose.loadFromFile("img/game_over.png", gRenderer))
	{
		printf("Failed to load car texture!\n");
		success = false;
	}

	if (!youWin.loadFromFile("img/you_win.png", gRenderer))
	{
		printf("Failed to load car texture!\n");
		success = false;
	}

	if (!gSpeedMeter.loadFromFile("img/speedMeter.png", gRenderer))
	{
		printf("Failed to load speed meter texture!\n");
		success = false;
	}
	else
	{
		const int SPEED_METER_HEIGHT = 133;
		const int SPEED_METER_WIDTH = 168;

		//Set sprite clips
		for (int i = 0; i < 46; i++)
		{

			gSpeedMeterClips[i].x = i * SPEED_METER_WIDTH;
			gSpeedMeterClips[i].y = 0;
			gSpeedMeterClips[i].w = SPEED_METER_WIDTH;
			gSpeedMeterClips[i].h = SPEED_METER_HEIGHT;				
		}
	}
	return success;
}

void Application::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Free the loaded sounds
	Mix_FreeChunk(beep);
	beep = NULL;
	Mix_FreeChunk(go);
	go = NULL;
	Mix_FreeMusic(menuBackgroundSound);
	menuBackgroundSound = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

void Application::menu()
{
	if (gWindow == NULL)
	{
		//Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
		}
	}
	menuBackgroundSound = Mix_LoadMUS("sounds/menu_background.mp3");
	Mix_PlayMusic(menuBackgroundSound, 10);
	LTexture menuBackgroundTexture;
	// menuBackgroundTexture.free();
	int buttonWidth = 160, buttonHeight = 50;
	int start = 0;

	//------------BUTTONS------------
	Button exitButton(buttonWidth, buttonHeight, 370, 600);
	Button startButton(buttonWidth, buttonHeight, 370, 200);
	Button instructionsButton(buttonWidth, buttonHeight, 650, 370);
	Button addDepositButton(buttonHeight, buttonHeight, 90, 135);
	Button removeDepositButton(buttonHeight, buttonHeight, 200, 135);
	Button makeDepositButton(buttonWidth, buttonHeight, 77, 180);
	Button addBetButton(buttonHeight, buttonHeight, 665, 135);
	Button removeBetButton(buttonHeight, buttonHeight, 775, 135);
	Button betButton(buttonWidth, buttonHeight, 650, 180);
	Button lastTenGamesButton(250, buttonHeight, 72, 370);
	Button onMusicButton(45, buttonHeight, 830, 10);
	Button offMusicButton(45, buttonHeight, 830, 10);

	//------------Text--------------
	LTexture menuTitle;
	LTexture exitButtonText;
	LTexture startButtonText;
	LTexture instructionText;
	LTexture creditText;
	LTexture creditNumber;
	LTexture depositNum;
	LTexture makeDepositText;
	LTexture betNum;
	LTexture betText;
	LTexture highScoresText;
	LTexture insertCreditText;
	LTexture insertCreditTextTwo;
	LTexture insertCreditTextThree;
	LTexture insertCreditTextFour;


	SDL_Color textColor = { 0x00, 0xCC, 0xFF };
	SDL_Color textYellow = { 0xFF, 0xFF, 0xFF };
	SDL_Color textRed = { 0xFF, 0x00, 0x00 };
	SDL_Color textGreen = { 0x00, 0xCC, 0x00 };
	SDL_Color textBlue = { 0x33, 0x66, 0xFF };


	//-------------BUTTON SET POS & BACKGROUND----------
	menuBackgroundTexture.loadFromFile("img/menu.png", gRenderer);

	startButton.loadMedia("img/buttons/button.png", *gRenderer);

	exitButton.loadMedia("img/buttons/button.png", *gRenderer);

	instructionsButton.loadMedia("img/buttons/button.png", *gRenderer);

	lastTenGamesButton.loadMedia("img/buttons/buttonOne.png", *gRenderer);

	addDepositButton.loadMedia("img/buttons/button-add.png", *gRenderer);

	removeDepositButton.loadMedia("img/buttons/button-remove.png", *gRenderer);

	makeDepositButton.loadMedia("img/buttons/button.png", *gRenderer);

	addBetButton.loadMedia("img/buttons/button-add.png", *gRenderer);

	removeBetButton.loadMedia("img/buttons/button-remove.png", *gRenderer);

	onMusicButton.loadMedia("img/onMusic.png", *gRenderer);

	offMusicButton.loadMedia("img/offMusic.png", *gRenderer);

	betButton.loadMedia("img/buttons/button.png", *gRenderer);

	//--------------TEXT LOADING---------

	menuTitle.loadFromRenderedText("Rally EGT", textColor, *gRenderer);
	startButtonText.loadFromRenderedText("Play", textColor, *gRenderer);
	exitButtonText.loadFromRenderedText("Exit Game", textColor, *gRenderer);
	instructionText.loadFromRenderedText("Instructions", textColor, *gRenderer);
	highScoresText.loadFromRenderedText("Last Ten Games", textColor, *gRenderer);
	creditText.loadFromRenderedText("Your credit: ", textColor, *gRenderer);
	creditNumber.loadFromRenderedText(std::to_string((int)this->startCredit), textColor, *gRenderer);
	depositNum.loadFromRenderedText(std::to_string(this->deposit), textColor, *gRenderer);
	makeDepositText.loadFromRenderedText("Make Deposit", textColor, *gRenderer);
	betNum.loadFromRenderedText(std::to_string((int)(playerBet)), textColor, *gRenderer);
	betText.loadFromRenderedText("Your Bet", textColor, *gRenderer);
	insertCreditText.loadFromRenderedText("Insert Credit", textRed, *gRenderer);
	insertCreditTextTwo.loadFromRenderedText("Insert Credit", textYellow, *gRenderer);
	insertCreditTextThree.loadFromRenderedText("Insert Credit", textBlue, *gRenderer);
	insertCreditTextFour.loadFromRenderedText("Insert Credit", textGreen, *gRenderer);

	lastTenGamesManager.createBlankFile();
	std::fstream gameFile("previousGames.txt", std::ios::out | std::ios::in);

	//Main loop flag
	bool quit = false;
	isMusicOn = true;
	//Event handler
	SDL_Event e;
	const int screenTicksPF = 1000 / screenFPS;
	Timer fpsTimer;
	Timer capTimer;
	fpsTimer.start();

	//While application is running
	while (!quit)
	{
		capTimer.start();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || exitButton.handleEvent(&e))
			{
				quit = true;
				gameFile.close();
			}
			else if (onMusicButton.handleEvent(&e))
			{
				if (isMusicOn)
				{
					isMusicOn = false;
					Mix_PauseMusic();
				}
				else
				{
					isMusicOn = true;
					if (Mix_PausedMusic() == 1)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PlayMusic(menuBackgroundSound, 10);
					}

				}
			}
			else if (startButton.handleEvent(&e) && playerBet > 0)
			{
				moneyManager.setCredit(this->startCredit);
				startTimeTemp = SDL_GetTicks();
				this->deposit = 0;
				depositNum.loadFromRenderedText(std::to_string(this->deposit), textColor, *gRenderer);
				int chosenCar = chooseCar(gRenderer, onMusicButton, offMusicButton);
				if (chosenCar != 0)
				{
					gameStart(gameFile, chosenCar, onMusicButton, offMusicButton);
				}
				else
				{
					continue;
				}
				if (isMusicOn)
				{
					Mix_PlayMusic(menuBackgroundSound, 10);
				}
				moneyManager.setCredit(this->startCredit);
				betNum.loadFromRenderedText(std::to_string((int)(playerBet)), textColor, *gRenderer);
				creditNumber.loadFromRenderedText(std::to_string((int)(this->startCredit)), textColor, *gRenderer);
			}
			else if (instructionsButton.handleEvent(&e))
			{
				instructionsScreen(onMusicButton, offMusicButton);
			}
			else if (lastTenGamesButton.handleEvent(&e))
			{
				lastTenGamesScreen(gameFile, onMusicButton, offMusicButton);
			}
			else if (addDepositButton.handleEvent(&e))
			{
				moneyManager.addDeposit(this->deposit);
				depositNum.loadFromRenderedText(std::to_string(deposit), textColor, *gRenderer);
			}
			else if (removeDepositButton.handleEvent(&e))
			{
				moneyManager.removeDeposit(this->deposit);
				depositNum.loadFromRenderedText(std::to_string(deposit), textColor, *gRenderer);
			}
			else if (makeDepositButton.handleEvent(&e))
			{
				moneyManager.makeDeposit(this->startCredit, this->deposit);
				creditNumber.loadFromRenderedText(std::to_string((int)(this->startCredit)), textColor, *gRenderer);
				depositNum.loadFromRenderedText(std::to_string(this->deposit), textColor, *gRenderer);
			}
			else if (addBetButton.handleEvent(&e))
			{
				moneyManager.makeBet(this->startCredit, this->playerBet);
				betNum.loadFromRenderedText(std::to_string((int)(playerBet)), textColor, *gRenderer);
			}
			else if (removeBetButton.handleEvent(&e))
			{
				moneyManager.removeBet(this->playerBet);
				betNum.loadFromRenderedText(std::to_string((int)(playerBet)), textColor, *gRenderer);
			}
		}
		//--------------CLEAR SCREEN-----------
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);


		//-------------RENDER BACKGROUNDS----------
		menuBackgroundTexture.render(*gRenderer, 0, 0);
		startButton.render(*gRenderer);
		exitButton.render(*gRenderer);
		startButton.render(*gRenderer);
		instructionsButton.render(*gRenderer);
		lastTenGamesButton.render(*gRenderer);
		addDepositButton.render(*gRenderer);
		removeDepositButton.render(*gRenderer);
		makeDepositButton.render(*gRenderer);
		addBetButton.render(*gRenderer);
		removeBetButton.render(*gRenderer);
		betButton.render(*gRenderer);
		if (isMusicOn)
		{
			onMusicButton.render(*gRenderer);
		}
		else
		{
			offMusicButton.render(*gRenderer);
		}

		//------------TEXT RENDERING --------------
		menuTitle.render(*gRenderer, (SCREEN_WIDTH - menuTitle.getWidth()) / 2, 100);
		startButtonText.render(*gRenderer, (SCREEN_WIDTH - startButtonText.getWidth()) / 2, 215);
		exitButtonText.render(*gRenderer, (SCREEN_WIDTH - exitButtonText.getWidth()) / 2, 614);
		instructionText.render(*gRenderer, 675, 385);
		highScoresText.render(*gRenderer, 105, 385);
		if (this->startCredit != 0)
		{
			creditText.render(*gRenderer, 50, 50);
			creditNumber.render(*gRenderer, 220, 50);
		}
		else
		{
			if (start == 0)
			{
				insertCreditText.render(*gRenderer, 100, 50);
			}
			else if (start == 1)
			{
				insertCreditTextTwo.render(*gRenderer, 100, 50);
			}
			else if (start == 2)
			{
				insertCreditTextThree.render(*gRenderer, 100, 50);
			}
			else if (start == 3)
			{
				insertCreditTextFour.render(*gRenderer, 100, 50);
			}
			start++;
			if (start == 4)
			{
				start /= 4;
			}
		}
		if (this->deposit < 10)
		{
			depositNum.render(*gRenderer, 157, 150);
		}
		else if (this->deposit < 100)
		{
			depositNum.render(*gRenderer, 147, 150);
		}
		else if (this->deposit == 100)
		{
			depositNum.render(*gRenderer, 142, 150);
		}

		makeDepositText.render(*gRenderer, 92, 197);

		if (this->playerBet < 10)
		{
			betNum.render(*gRenderer, 734, 150);
		}
		else if (this->playerBet < 100)
		{
			betNum.render(*gRenderer, 724, 150);
		}
		else if (this->playerBet == 100)
		{
			betNum.render(*gRenderer, 719, 150);
		}

		betText.render(*gRenderer, 691, 197);


		//------------- UPDATE SCREEN----------------
		SDL_RenderPresent(gRenderer);

		int frameTicks = capTimer.getTicks();
		if (frameTicks < screenTicksPF)
		{
			SDL_Delay(screenTicksPF - frameTicks);
		}
	}
}

void Application::gameStart(std::fstream& fileToRead, int& choosenCar, Button& onMusicButton, Button& offMusicButton)
{
	if (gWindow != NULL)
	{
		if (!loadMedia(choosenCar))
		{
			printf("Failed to load media!\n");
		}
	}

	//Main loop flag
	bool quit = false;

	int timeTemp = this->time;

	//Event handler
	SDL_Event e;
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
	LTexture timeTexture;

	//
	bool firstRun = true;

	switch (choosenCar)
	{
		case carOne: gCarTexture = gFirstCarTexture; break;
		case carTwo: gCarTexture = gSecondCarTexture; break;
		case carThree: gCarTexture = gThirdCarTexture; break;
	}

	//The car that will be moving around on the screen
	Car car(choosenCar, gCarTexture.getWidth(), gCarTexture.getHeight(), startingAngle, map.getDifficulty());
	SDL_Rect* wall = map.getObstacles();
	this->startGame = obj.getCurrentTime(obj.getCurrentDateTime());

	if (isMusicOn)
	{
		car.loadSounds();
	}

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//Handle input for the car
			car.handleEvent(e);

			if (onMusicButton.handleEvent(&e))
			{
				if (isMusicOn)
				{
					isMusicOn = false;
					car.closeSounds();
				}
				else
				{
					isMusicOn = true;
					car.loadSounds();
				}
			}
		}

		if (firstRun)
		{
			if (isMusicOn)
			{
				loadingScreen(gRenderer, timeTexture, textColor, car, onMusicButton);
			}
			else
			{
				loadingScreen(gRenderer, timeTexture, textColor, car, offMusicButton);
			}
			firstRun = false;
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gBackgroundTexture.render(*gRenderer, 0, 0);

		timeTexture.render(*gRenderer, 620, 10);

		if (isMusicOn)
		{
			onMusicButton.render(*gRenderer);
		}
		else
		{
			offMusicButton.render(*gRenderer);
		}

		if (SDL_GetTicks() - startTimeTemp >= 1000)
		{

			if (!timeTexture.loadFromRenderedText(timer(timeTemp), textColor, *gRenderer))
			{
				printf("Unable to render time texture!\n");
			}
			timer(timeTemp--);
			startTimeTemp = SDL_GetTicks();
		}

		//test the obstacles
		//drawObstaclesHelper(*gRenderer, wall, map.getObstaclesNumber());

		//Move the car and check collision
		car.move(wall, map.getObstaclesNumber(), SCREEN_HEIGHT, SCREEN_WIDTH);

		if (timeTemp < 0)
		{
			//YOU LOSE
			this->endGame = obj.getCurrentTime(obj.getCurrentDateTime());
			this->realTime = this->time;
			this->playerWin = 0;

			obj.writeXmlToFile(this->startGame, this->endGame, this->time, this->realTime,
				this->startCredit, this->playerBet, this->playerWin, this->coef);

			this->startCredit = this->startCredit - this->playerBet;
			lastTenGamesManager.writeLastTenGames(fileToRead, this->startCredit, this->realTime, this->playerBet, this->playerWin, this->coef);
			this->playerBet = 0;
			Mix_HaltMusic();
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			youLose.render(*gRenderer, 0, 0);

			SDL_RenderPresent(gRenderer);
			SDL_Delay(1500);
			return;
		}
		else if (car.getCarX() >= 870 && car.getCarY() >= 620)
		{
			//YOU WIN
			this->endGame = obj.getCurrentTime(obj.getCurrentDateTime());
			this->realTime = this->time - timeTemp;
			this->playerWin = this->estimatedPlayerWin;

			obj.writeXmlToFile(this->startGame, this->endGame, this->time, this->realTime,
				this->startCredit, this->playerBet, this->playerWin, this->coef);

			this->startCredit = this->startCredit + this->playerWin;
			lastTenGamesManager.writeLastTenGames(fileToRead, this->startCredit, this->realTime, this->playerBet, this->playerWin, this->coef);
			this->playerBet = 0;
			Mix_HaltMusic();
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			youWin.render(*gRenderer, 0, 0);

			SDL_RenderPresent(gRenderer);
			SDL_Delay(1500);

			return;
		}
		//Render car
		car.render(gCarTexture, gSpeedMeter, gSpeedMeterClips, *gRenderer);

		//UPDATE SCREEN
		SDL_RenderPresent(gRenderer);
	}
}

void Application::loadingScreen(SDL_Renderer* gRenderer, LTexture& timeTexture, SDL_Color& textColor, Car &car, Button& musicButton)
{
	LTexture one, two, three;

	if (!one.loadFromFile("img/One.png", gRenderer))
	{
		printf("Failed to load one.png !\n");
	}

	if (!two.loadFromFile("img/Two.png", gRenderer))
	{
		printf("Failed to load two.png!\n");
	}

	if (!three.loadFromFile("img/Three.png", gRenderer))
	{
		printf("Failed to load three.png !\n");
	}

	Mix_HaltMusic();
	beep = Mix_LoadWAV("sounds/beep.wav");
	go = Mix_LoadWAV("sounds/go.wav");
	if (beep == NULL)
	{
		printf("Failed to load beep.wav !\n");
	}
	if (go == NULL)
	{
		printf("Failed to load go.wav !\n");
	}
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBackgroundTexture.render(*gRenderer, 0, 0);
	musicButton.render(*gRenderer);
	three.render(*gRenderer, 0, 0);


	timeTexture.loadFromRenderedText(timer(this->time), textColor, *gRenderer);
	car.render(gCarTexture, gSpeedMeter, gSpeedMeterClips, *gRenderer);
	timeTexture.render(*gRenderer, 620, 10);

	if (isMusicOn)
	{
		Mix_PlayChannel(-1, beep, 0);
	}
	SDL_RenderPresent(gRenderer);
	SDL_Delay(1000);

	///

	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBackgroundTexture.render(*gRenderer, 0, 0);
	musicButton.render(*gRenderer);
	two.render(*gRenderer, 0, 0);

	timeTexture.loadFromRenderedText(timer(this->time), textColor, *gRenderer);
	timeTexture.render(*gRenderer, 620, 10);
	car.render(gCarTexture, gSpeedMeter, gSpeedMeterClips, *gRenderer);

	if (isMusicOn)
	{
		Mix_PlayChannel(-1, beep, 0);
	}
	SDL_RenderPresent(gRenderer);
	SDL_Delay(1000);

	///

	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gBackgroundTexture.render(*gRenderer, 0, 0);
	musicButton.render(*gRenderer);
	one.render(*gRenderer, 0, 0);

	timeTexture.loadFromRenderedText(timer(this->time), textColor, *gRenderer);
	timeTexture.render(*gRenderer, 620, 10);
	car.render(gCarTexture, gSpeedMeter, gSpeedMeterClips, *gRenderer);

	if (isMusicOn)
	{
		Mix_PlayChannel(-1, beep, 0);
	}
	SDL_RenderPresent(gRenderer);
	SDL_Delay(1000);
	if (isMusicOn)
	{
		Mix_PlayChannel(-1, go, 0);
	}

}

void Application::instructionsScreen(Button& onMusicButton, Button& offMusicButton)
{

	if (gWindow == NULL)
	{
		printf("Failed to load media!\n");
	}

	//Main loop flag
	bool quit = false;

	//Text Color
	SDL_Color textColor = { 0x00, 0xCC, 0xFF };

	//Back button
	Button back(160, 50, 370, 600);

	//Textures
	LTexture backgroundTexture;
	LTexture arrows;
	LTexture backText;
	LTexture instructions;
	LTexture instructionsTwo;
	LTexture instructionsUp;
	LTexture instructionsBack;
	LTexture instructionsLeft;
	LTexture instructionsLeftOne;
	LTexture instructionsLeftTwo;
	LTexture instructionsRight;
	LTexture instructionsRightOne;
	LTexture instructionsRightTwo;
	LTexture instructionsChoice;
	LTexture slogan;
	LTexture sloganTwo;


	//-------------BUTTON SET POS & BCKGROUND----------
	backgroundTexture.loadFromFile("img/menu.png", gRenderer);
	back.loadMedia("img/buttons/button.png", *gRenderer);
	arrows.loadFromFile("img/arrowKeys.png", gRenderer);


	//------------------TEXT LOADING-------------------
	backText.loadFromRenderedText("Back", textColor, *gRenderer);
	instructions.loadFromRenderedText("The goal is to reach the finish line before the time runs out!", textColor, *gRenderer);
	instructionsTwo.loadFromRenderedText("Get moving around using the arrow keys as follows :", textColor, *gRenderer);
	instructionsUp.loadFromRenderedText("Up - accelerate the car towards it's fornt.", textColor, *gRenderer);
	instructionsBack.loadFromRenderedText("Down - start driving the car in reverse.", textColor, *gRenderer);
	instructionsLeftOne.loadFromRenderedText("Left:", textColor, *gRenderer);
	instructionsLeft.loadFromRenderedText("Hold it at least 0.3 sec and release", textColor, *gRenderer);
	instructionsLeftTwo.loadFromRenderedText("to turn the car in this direction.", textColor, *gRenderer);
	instructionsRightOne.loadFromRenderedText("Right:", textColor, *gRenderer);
	instructionsRight.loadFromRenderedText("Hold it atleast 0.3 sec and release", textColor, *gRenderer);
	instructionsRightTwo.loadFromRenderedText("to turn the car in this direction.", textColor, *gRenderer);
	slogan.loadFromRenderedText("Good luck!", textColor, *gRenderer);
	sloganTwo.loadFromRenderedText("And may the Gods be ever in your favour!", textColor, *gRenderer);
	instructionsChoice.loadFromRenderedText("When you choose your car, press enter to begin the game", textColor, *gRenderer);


	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (onMusicButton.handleEvent(&e))
			{
				if (isMusicOn)
				{
					isMusicOn = false;
					Mix_PauseMusic();
				}
				else
				{
					isMusicOn = true;
					Mix_ResumeMusic();
				}
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				return;
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (back.handleEvent(&e))
				{
					return;
				}
			}
		}

		//--------------CLEAR SCREEN-----------
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//---------------RENDER TEXT----------------
		backgroundTexture.render(*gRenderer, 0, 0);
		arrows.render(*gRenderer, ((SCREEN_WIDTH - arrows.getWidth()) / 2), 200);
		back.render(*gRenderer);
		backText.render(*gRenderer, ((SCREEN_WIDTH - backText.getWidth()) / 2), 614);
		instructions.render(*gRenderer, ((SCREEN_WIDTH - instructions.getWidth()) / 2), 50);
		instructionsTwo.render(*gRenderer, ((SCREEN_WIDTH - instructionsTwo.getWidth()) / 2), 100);
		instructionsUp.render(*gRenderer, ((SCREEN_WIDTH - instructionsUp.getWidth()) / 2), 150);
		instructionsBack.render(*gRenderer, ((SCREEN_WIDTH - instructionsUp.getWidth()) / 2), 370);
		instructionsLeft.render(*gRenderer, 0, 230);
		instructionsLeftOne.render(*gRenderer, ((SCREEN_WIDTH - instructionsLeftOne.getWidth()) / 6), 200);
		instructionsLeftTwo.render(*gRenderer, 10, 270);
		instructionsRight.render(*gRenderer, 540, 230);
		instructionsRightOne.render(*gRenderer, 680, 200);
		instructionsRightTwo.render(*gRenderer, 560, 270);
		slogan.render(*gRenderer, ((SCREEN_WIDTH - slogan.getWidth()) / 2), 510);
		sloganTwo.render(*gRenderer, ((SCREEN_WIDTH - sloganTwo.getWidth()) / 2), 540);
		instructionsChoice.render(*gRenderer, ((SCREEN_WIDTH - instructionsChoice.getWidth()) / 2), 450);

		if (isMusicOn)
		{
			onMusicButton.render(*gRenderer);
		}
		else
		{
			offMusicButton.render(*gRenderer);
		}


		//------------- UPDATE SCREEN----------------
		SDL_RenderPresent(gRenderer);
	}
}

void Application::lastTenGamesScreen(std::fstream& fileToRead, Button& onMusicButton, Button& offMusicButton)
{
	if (gWindow == NULL)
	{
		printf("Unable to open window");
	}
	bool quit = false;
	//Main loop flag
	SDL_Color textColor = { 0x00, 0xCC, 0xFF };
	LTexture backgroundTexture;
	Button back(160, 50, 370, 600);
	LTexture backText;
	LTexture description;
	std::string descriptionText = "Player Credit";
	descriptionText.append("             ");
	descriptionText.append("Time");
	descriptionText.append("                  ");
	descriptionText.append("Player Bet");
	descriptionText.append("                ");
	descriptionText.append("Player Win");
	descriptionText.append("                ");
	descriptionText.append("Difficulty");
	std::vector<PreviousGame> lastTenGames = lastTenGamesManager.readLastTenGames(fileToRead);

	LTexture lastTenGamesCredit[10];
	LTexture lastTenGamesTime[10];
	LTexture lastTenGamesBet[10];
	LTexture lastTenGamesWin[10];
	LTexture lastTenGamesDiff[10];
	for (int i = 0; i < 10; i++)
	{
		std::string tempCredit = std::to_string((int)lastTenGames[i].getCredit());
		std::string tempTime = std::to_string(lastTenGames[i].getTime());
		std::string tempBet = std::to_string((int)lastTenGames[i].getPlayerBet());
		std::string tempWin = std::to_string((int)lastTenGames[i].getPlayerWin());
		std::string tempDiff = lastTenGames[i].getDifficulty();

		lastTenGamesCredit[i].loadFromRenderedText(tempCredit, textColor, *gRenderer);
		lastTenGamesTime[i].loadFromRenderedText(tempTime, textColor, *gRenderer);
		lastTenGamesBet[i].loadFromRenderedText(tempBet, textColor, *gRenderer);
		lastTenGamesWin[i].loadFromRenderedText(tempWin, textColor, *gRenderer);
		lastTenGamesDiff[i].loadFromRenderedText(tempDiff, textColor, *gRenderer);
	}

	//----------------TEXTURES LOADING ------------------
	backgroundTexture.loadFromFile("img/menu.png", gRenderer);
	back.setPosition(370, 600);
	back.loadMedia("img/buttons/button.png", *gRenderer);



	//------------------TEXT LOADING-------------------
	backText.loadFromRenderedText("Back", textColor, *gRenderer);
	description.loadFromRenderedText(descriptionText, textColor, *gRenderer);

	//Event handler
	SDL_Event e;


	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (onMusicButton.handleEvent(&e))
			{
				if (isMusicOn)
				{
					isMusicOn = false;
					Mix_PauseMusic();
				}
				else
				{
					isMusicOn = true;
					Mix_ResumeMusic();
				}
			}
			else if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				return;
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (back.handleEvent(&e))
				{
					return;
				}
			}
		}

		//--------------CLEAR SCREEN-----------
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//---------------RENDER TEXT----------------
		backgroundTexture.render(*gRenderer, 0, 0);
		back.render(*gRenderer);
		backText.render(*gRenderer, ((SCREEN_WIDTH - backText.getWidth()) / 2), 614);
		description.render(*gRenderer, 20, 60);
		int xPos = 0;
		for (int i = 0; i < 10; i++)
		{
			if (lastTenGames[i].getCredit() < 10)
			{
				lastTenGamesCredit[i].render(*gRenderer, 85, (xPos + 100));
			}
			else
			{
				lastTenGamesCredit[i].render(*gRenderer, 80, (xPos + 100));
			}
			lastTenGamesTime[i].render(*gRenderer, 240, (xPos + 100));
			if (lastTenGames[i].getPlayerBet() < 10)
			{
				lastTenGamesBet[i].render(*gRenderer, 417, (xPos + 100));
			}
			else
			{
				lastTenGamesBet[i].render(*gRenderer, 410, (xPos + 100));
			}
			lastTenGamesWin[i].render(*gRenderer, 630, (xPos + 100));
			if (lastTenGames[i].getDifficulty() != "Medium")
			{
				lastTenGamesDiff[i].render(*gRenderer, 795, (xPos + 100));
			}
			else
			{
				lastTenGamesDiff[i].render(*gRenderer, 780, (xPos + 100));
			}
			xPos += 45;
		}
		if (isMusicOn)
		{
			onMusicButton.render(*gRenderer);
		}
		else
		{
			offMusicButton.render(*gRenderer);
		}

		//------------- UPDATE SCREEN----------------
		SDL_RenderPresent(gRenderer);
	}
}

int Application::chooseCar(SDL_Renderer* gRenderer, Button& onMusicButton, Button& offMusicButton)
{
	if (gWindow == NULL)
	{
		printf("Failed to load screen!\n");
	}

	bool quit = false;
	//Main loop flag
	SDL_Color textColor = { 0x00, 0xCC, 0xFF };
	Button back(160, 50, 370, 600);
	LTexture backgroundTexture;
	LTexture header;
	LTexture cursor;
	LTexture attributesCarOne;
	LTexture attributesCarTwo;
	LTexture attributesCarThree;
	LTexture backText;
	LTexture text;
	LTexture carOne;
	LTexture carTwo;
	LTexture carThree;

	int cursorX = 190;
	int cursorY = 90;
	//--------------BACKGROUND IMG-----------------
	backgroundTexture.loadFromFile("img/menu.png", gRenderer);

	//--------------CURSOR IMG --------------------
	cursor.loadFromFile("img/cars/cursor.png", gRenderer);

	//----------------ATTRIBUTES--------------
	attributesCarOne.loadFromFile("img/cars/fastest.png", gRenderer);
	attributesCarTwo.loadFromFile("img/cars/medium.png", gRenderer);
	attributesCarThree.loadFromFile("img/cars/slowest.png", gRenderer);

	//-------------BUTTON SET POS & BCKGROUND----------
	back.setPosition(370, 600);
	back.loadMedia("img/buttons/button.png", *gRenderer);


	//---------------CAR PICTURES----------------
	carOne.loadFromFile("img/cars/carOneLarge.png", gRenderer);
	carTwo.loadFromFile("img/cars/carTwoLarge.png", gRenderer);
	carThree.loadFromFile("img/cars/carThreeLarge.png", gRenderer);


	//------------------TEXT LOADING-------------------
	backText.loadFromRenderedText("Back", textColor, *gRenderer);
	header.loadFromRenderedText("Choose your vehicle", textColor, *gRenderer);
	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (onMusicButton.handleEvent(&e))
			{
				if (isMusicOn)
				{
					isMusicOn = false;
					Mix_PauseMusic();
				}
				else
				{
					isMusicOn = true;
					Mix_ResumeMusic();
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (back.handleEvent(&e))
				{
					return 0;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					cursorX += 200;
					if (cursorX > 590)
					{
						cursorX = 590;
					}
					break;
				case SDLK_LEFT:
					cursorX -= 200;
					if (cursorX < 190)
					{
						cursorX = 190;
					}
					break;
				case SDLK_RETURN:
					if (cursorX == 190)
					{
						return 1;
					}
					else if (cursorX == 390)
					{
						return 2;
					}
					else
					{
						return 3;
					}
					break;
				case SDLK_ESCAPE:
					return 0;
					break;
				default:
					break;
				}
			}
		}

		//--------------CLEAR SCREEN-----------
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//---------------RENDER TEXT AND TEXTURES----------------
		backgroundTexture.render(*gRenderer, 0, 0);
		header.render(*gRenderer, ((SCREEN_WIDTH - header.getWidth()) / 2), 30);
		back.render(*gRenderer);
		backText.render(*gRenderer, ((SCREEN_WIDTH - backText.getWidth()) / 2), 614);
		carOne.render(*gRenderer, 200, 100);
		carTwo.render(*gRenderer, 400, 100);
		carThree.render(*gRenderer, 600, 100);
		cursor.render(*gRenderer, cursorX, cursorY);

		if (isMusicOn)
		{
			onMusicButton.render(*gRenderer);
		}
		else
		{
			offMusicButton.render(*gRenderer);
		}

		if (cursorX == 190)
		{
			attributesCarOne.render(*gRenderer, ((SCREEN_WIDTH - attributesCarOne.getWidth()) / 2), 300);
		}
		else if (cursorX == 390)
		{
			attributesCarTwo.render(*gRenderer, ((SCREEN_WIDTH - attributesCarTwo.getWidth()) / 2), 300);
		}
		else
		{
			attributesCarThree.render(*gRenderer, ((SCREEN_WIDTH - attributesCarThree.getWidth()) / 2), 300);
		}

		//------------- UPDATE SCREEN----------------
		SDL_RenderPresent(gRenderer);
	}
	return 0;
}

std::string Application::timer(int availiableTime)
{
	int seconds = availiableTime;
	std::string timeText;
	timeText = "Time left: " + std::to_string(availiableTime);

	return timeText;
}

void Application::drawObstaclesHelper(SDL_Renderer& renderer, SDL_Rect* wall, int obstacleNumber)
{
	for (int i = 0; i < obstacleNumber; i++)
	{
		SDL_Rect* tempWall = &wall[i];
		SDL_SetRenderDrawColor(&renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(&renderer, tempWall);
	}
}
