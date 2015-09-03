#pragma once
#include "Globals.h"
#include "LTexture.h"
class Car
{
public:

	//Initializes the variables
	Car(int, int, int, double, int);
	~Car();

	void moveForward(int&);
	void moveBackward(int&);
	void accelerate();
	void slowDown();
	void impactSlowDown();
	void updateCarPosition();

	//Takes key presses and adjusts the car's velocity
	void handleEvent(SDL_Event& e);

	void loadSounds();
	void closeSounds();

	//Moves the car and checks collision
	void move(SDL_Rect wall[], int obstaclesNumber, int SCREEN_HEIGHT, int SCREEN_WIDTH);
	
	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Shows the car on the screen
	void render(LTexture&, LTexture&, SDL_Rect[], SDL_Renderer&);

	void setCarCharacteristics(int&);

	void setCarX(double);
	double getCarX() const;

	void setCarY(double);
	double getCarY() const;

	void setTopSpeed(double);
	double getTopSpeed() const;

	void setAcceleration(double);
	double getAcceleration() const;

	void setTraction(double);
	double getTraction() const;

	void setBraking(double);
	double getBraking() const;

	void setSpeedMeterX(int);
	int getSpeedMeterX() const;

	void setSpeedMeterY(int);
	int getSpeedMeterY() const;

private:
	int PICTURE_WIDTH;
	int PICTURE_HEIGHT;

	//The dimensions of the car
	int CAR_WIDTH;
	int CAR_HEIGHT;

	//Maximum axis velocity of the car
	double CAR_VEL;

	//The X and Y offsets of the car
	double mPosX, mPosY;
	double angle;

	//The velocity of the car
	double mVelX, mVelY;

	//Car's collision box
	SDL_Rect mCollider;

	//Car sounds
	Mix_Chunk* tire;
	Mix_Chunk* crash;
	Mix_Chunk* takePowerUp;
	Mix_Music* engine;

	//Car characteristics
	double topSpeed;
	double acceleration;
	double traction;
	double braking;

	int speedMeterX;
	int speedMeterY;

	enum forwardDirection { North = 0, East, South, West };
	enum cars { carOne = 1, carTwo, carThree };

	int direction;
	clock_t turningClock;
	clock_t driftingClock, accelerateClock, brakesClock;

	bool isPowerUpPicked;
};