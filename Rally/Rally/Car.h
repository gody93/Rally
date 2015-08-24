#pragma once
#include "Globals.h"
#include "LTexture.h"
class Car
{
public:

	//Initializes the variables
	Car(int,int,double);

	void moveForward(int);
	void moveBackward(int);
	void updateCar();

	int getCarX() const;
	int getCarY() const;

	//Takes key presses and adjusts the car's velocity
	void handleEvent(SDL_Event& e);

	void tireSound();
	void engineSound();
	void close();

	//Moves the car and checks collision
	void move(SDL_Rect wall[], int SCREEN_WIDTH, int SCREEN_HEIGHT, int obstaclesNumber);

	//Box collision detector
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Shows the car on the screen
	void render(LTexture&, SDL_Renderer&);

private:
	int PICTURE_WIDTH;
	int PICTURE_HEIGHT;

	//The dimensions of the car
	int CAR_WIDTH;
	int CAR_HEIGHT;

	//Maximum axis velocity of the car
	const int CAR_VEL = 2;

	//The X and Y offsets of the car
	int mPosX, mPosY;
	double angle;

	//The velocity of the car
	int mVelX, mVelY;

	//Car's collision box
	SDL_Rect mCollider;

	Mix_Chunk* tire;
	Mix_Music* engine;

	enum forwardDirection { North = 0, East, South, West };

	int direction;
	clock_t start;
};