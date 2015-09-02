#include "Car.h"

Car::Car(int width, int height, double startingAngle) : PICTURE_WIDTH(width), PICTURE_HEIGHT(height), angle(startingAngle), CAR_VEL(0)
{
	setTopSpeed(4.4);
	setTraction(0.3);
	setAcceleration(0.2);
	setBraking(0.05);

	updateCarPosition();
	if (angle == 0)
	{
		mPosX = 10;
		mPosY = 0;
	}
	else
	{
		mPosX = 6;
		mPosY = 10;
	}

	//Set collision box dimension
	mCollider.w = CAR_WIDTH;
	mCollider.h = CAR_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

Car::~Car()
{
	closeSounds();
}

void Car::moveForward(int& direction)
{
	switch (direction)
	{
	case North: mVelY -= CAR_VEL; break;
	case East: mVelX += CAR_VEL; break;
	case South: mVelY += CAR_VEL; break;
	case West: mVelX -= CAR_VEL; break;
	}
}

void Car::moveBackward(int& direction)
{
	switch (direction)
	{
	case North: mVelY += CAR_VEL; break;
	case East: mVelX -= CAR_VEL; break;
	case South: mVelY -= CAR_VEL; break;
	case West: mVelX += CAR_VEL; break;
	}
}

void Car::accelerate()
{
	moveBackward(direction);
	if (CAR_VEL <= this->topSpeed)
	{
		CAR_VEL += 0.1;
	}
	moveForward(direction);
}

void Car::passiveBrakes()
{
	moveBackward(direction);
	if (CAR_VEL > 0)
	{
		CAR_VEL -= 0.001;
	}
	else
	{
		CAR_VEL = 0;
	}
	moveForward(direction);
}

void Car::brakes()
{
	moveBackward(direction);
	if (CAR_VEL > 0)
	{
		CAR_VEL -= 0.1;
	}
	else
	{
		CAR_VEL = 0;
	}
	moveForward(direction);
}

void Car::updateCarPosition()
{
	if (angle >= 360)
	{
		angle -= 360;
	}
	else if (angle < 0)
	{
		angle += 360;
	}

	if (angle == 0)
	{
		direction = South;
		CAR_WIDTH = PICTURE_WIDTH;
		CAR_HEIGHT = PICTURE_HEIGHT;

		mCollider.w = PICTURE_WIDTH;
		mCollider.h = PICTURE_HEIGHT;
	}
	else if (angle == 90)
	{
		direction = West;
		CAR_WIDTH = PICTURE_HEIGHT;
		CAR_HEIGHT = PICTURE_WIDTH;

		mCollider.w = PICTURE_HEIGHT;
		mCollider.h = PICTURE_WIDTH;
	}
	else if (angle == 180)
	{
		direction = North;
		CAR_WIDTH = PICTURE_WIDTH;
		CAR_HEIGHT = PICTURE_HEIGHT;

		mCollider.w = PICTURE_WIDTH;
		mCollider.h = PICTURE_HEIGHT;
	}
	else if (angle == 270)
	{
		direction = East;
		CAR_WIDTH = PICTURE_HEIGHT;
		CAR_HEIGHT = PICTURE_WIDTH;

		mCollider.w = PICTURE_HEIGHT;
		mCollider.h = PICTURE_WIDTH;
	}
}

void Car::handleEvent(SDL_Event& e)
{
	updateCarPosition();

	std::cout << "mVelX: " << mVelX << std::endl;
	std::cout << "mVelY: " << mVelY << std::endl;
	std::cout << "CAR_VEL: " << CAR_VEL << std::endl << std::endl;

	//If a key was pressed once
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (mVelX == 0 && mVelY == 0)
			{
				moveForward(direction);
			}
	
			Mix_PlayMusic(engine, 0);
			accelerateClock = std::clock();
			break;

		case SDLK_DOWN:
			brakes();
			brakesClock = std::clock();
			break;
		case SDLK_LEFT:
			Mix_PlayChannel(-1, tire, 0);
			turningClock = std::clock();
			driftingClock = std::clock();
			angle -= 45;
			break;
		case SDLK_RIGHT:
			Mix_PlayChannel(-1, tire, 0);
			turningClock = std::clock();
			driftingClock = std::clock();
			angle += 45;
			break;
		}
	}
	//If a key was pressed and repeat
	else if (e.type == SDL_KEYDOWN && e.key.repeat != 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if ((std::clock() - accelerateClock) / (double)CLOCKS_PER_SEC > this->acceleration)
			{
				accelerate();
				accelerateClock = std::clock();
			}
			break;
		case SDLK_DOWN:
			if ((std::clock() - brakesClock) / (double)CLOCKS_PER_SEC > this->braking)
			{
				brakes();
				brakesClock = std::clock();
			}
			break;
		case SDLK_LEFT:
			if ((std::clock() - driftingClock) / (double)CLOCKS_PER_SEC > 0.1)
			{
				brakes();
				driftingClock = std::clock();
			}
			break;
		case SDLK_RIGHT:
			if ((std::clock() - driftingClock) / (double)CLOCKS_PER_SEC > 0.1)
			{
				brakes();
				driftingClock = std::clock();
			}
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Mix_HaltMusic();
			//moveForward(direction);
			break;
		case SDLK_DOWN: brakes(); break;
		case SDLK_LEFT:
			if ((std::clock() - turningClock) / (double)CLOCKS_PER_SEC > this->traction)
			{
				angle -= 45;
				mVelX = 0;
				mVelY = 0;
			}
			else
			{
				angle += 45;
			}
			break;
		case SDLK_RIGHT:
			if ((std::clock() - turningClock) / (double)CLOCKS_PER_SEC > this->traction)
			{
				angle += 45;
				mVelX = 0;
				mVelY = 0;
			}
			else
			{
				angle -= 45;
			}
			break;
		}
	}
}

bool Car::checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Car::move(SDL_Rect wall[], int SCREEN_WIDTH, int SCREEN_HEIGHT, int obstaclesNumber)
{
	//Move the car left or right
	mPosX += mVelX;
	mCollider.x = (int)ceil(mPosX);

	for (int i = 0; i < obstaclesNumber; i++)
	{
		//If the car collided or went too far to the left or right
		if ((mPosX < 0) || (mPosX + CAR_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, wall[i]))
		{
			//Move back
			mPosX -= mVelX;
			mCollider.x = (int)ceil(mPosX);
		}
	}

	//Move the car up or down
	mPosY += mVelY;
	mCollider.y = (int)ceil(mPosY);

	for (int i = 0; i < obstaclesNumber; i++)
	{
		//If the car collided or went too far up or down
		if ((mPosY < 0) || (mPosY + CAR_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, wall[i]))
		{
			//Move back
			mPosY -= mVelY;
			mCollider.y = (int)ceil(mPosY);
		}
	}
	if (abs(mVelX - mVelY) != CAR_VEL)
	{
		mVelY = 0;
		mVelX = 0;
	}
}

void Car::render(LTexture& gCarTexture, LTexture gSpeedMeter[], SDL_Renderer& renderer)
{
	//Show the car
	gCarTexture.render(renderer, mPosX, mPosY, NULL, angle);
	gSpeedMeter[(int)floor(this->CAR_VEL / 0.2)].render(renderer, 20, 500, NULL, 0);
}

void Car::setCarX(double mPosX)
{
	this->mPosX = mPosX;
}

double Car::getCarX() const
{
	return this->mPosX;
}

void Car::setCarY(double mPosY)
{
	this->mPosY = mPosY;
}

double Car::getCarY() const
{
	return this->mPosY;
}

void Car::setTopSpeed(double topSpeed)
{
	this->topSpeed = topSpeed;
}

double Car::getTopSpeed() const
{
	return this->topSpeed;
}

void Car::setAcceleration(double acceleration)
{
	this->acceleration = acceleration;
}

double Car::getAcceleration() const
{
	return this->acceleration;
}

void Car::setTraction(double traction)
{
	this->traction = traction;
}

double Car::getTraction() const
{
	return this->traction;
}

void Car::setBraking(double braking)
{
	this->braking = braking;
}

double Car::getBraking() const
{
	return this->braking;
}

void Car::loadSounds()
{
	this->engine = Mix_LoadMUS("sounds/engine.mp3");
	if (!engine)
	{
		std::cerr << "Sound cannot be loaded." << Mix_GetError << std::endl;
	}

	this->tire = Mix_LoadWAV("sounds/tires.wav");
	if (!tire)
	{
		std::cerr << "Sound cannot be loaded." << Mix_GetError << std::endl;
	}
}

void Car::closeSounds()
{
	Mix_FreeChunk(tire);
	tire = NULL;
	Mix_FreeMusic(engine);
	engine = NULL;
}