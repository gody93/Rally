#pragma once
#include "Globals.h"
#include "LTexture.h"
class Car
{
public:

	//Initializes the variables
	Car(int, int, double);
	~Car();

	void moveForward(int&);
	void moveBackward(int&);
	void accelerate();
	void brakes();
	void passiveBrakes();
	void updateCarPosition();

	//Takes key presses and adjusts the car's velocity
	void handleEvent(SDL_Event& e);

	void loadSounds();
	void closeSounds();

	//Moves the car and checks collision
	void move(SDL_Rect wall[], int SCREEN_WIDTH, int SCREEN_HEIGHT, int obstaclesNumber);

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Shows the car on the screen
	void render(LTexture&, LTexture[], SDL_Renderer&);

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
	Mix_Music* engine;

	//Car characteristics
	double topSpeed;
	double acceleration;
	double traction;
	double braking;

	enum forwardDirection { North = 0, East, South, West };

	int direction;
	clock_t turningClock;
	clock_t driftingClock, accelerateClock, brakesClock;
};