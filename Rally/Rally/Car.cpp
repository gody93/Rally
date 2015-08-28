#include "Car.h"

Car::Car(int width, int height, double startingAngle) : PICTURE_WIDTH(width), PICTURE_HEIGHT(height), angle(startingAngle)
{

	engineSound();
	tireSound();
	updateCar();
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

void Car::moveForward(int direction)
{
	switch (direction)
	{
	case North: mVelY -= CAR_VEL; break;
	case East: mVelX += CAR_VEL; break;
	case South: mVelY += CAR_VEL; break;
	case West: mVelX -= CAR_VEL; break;
	default:
		break;
	}
}

void Car::moveBackward(int direction)
{
	switch (direction)
	{
	case North: mVelY += CAR_VEL; break;
	case East: mVelX -= CAR_VEL; break;
	case South: mVelY -= CAR_VEL; break;
	case West: mVelX += CAR_VEL; break;
	default:
		break;
	}
}

void Car::updateCar()
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
	updateCar();

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: moveForward(direction);
			Mix_PlayMusic(engine, 0);
			break;
			
		case SDLK_DOWN: moveBackward(direction); break;
		case SDLK_LEFT:
			Mix_PlayChannel(-1, tire, 0);
			start = clock();
			angle -= 45;
			break;
		case SDLK_RIGHT:
			Mix_PlayChannel(-1, tire, 0);
			start = clock();
			angle += 45;
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
			moveBackward(direction);break;
		case SDLK_DOWN: moveForward(direction); break;
		case SDLK_LEFT:
			if ((std::clock() - start) / (double)CLOCKS_PER_SEC > 0.3)
			{
				angle -= 45;
			}
			else
			{
				angle += 45;
			}
			break;
		case SDLK_RIGHT:
			if ((std::clock() - start) / (double)CLOCKS_PER_SEC > 0.3)
			{
				angle += 45;
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
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

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
	//Move the dot left or right
	mPosX += mVelX;
	mCollider.x = mPosX;

	for (int i = 0; i < obstaclesNumber; i++)
	{
		//If the dot collided or went too far to the left or right
		if ((mPosX < 0) || (mPosX + CAR_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, wall[i]))
		{
			//Move back
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}
	}

	//Move the dot up or down
	mPosY += mVelY;
	mCollider.y = mPosY;

	for (int i = 0; i < obstaclesNumber; i++)
	{
		//If the dot collided or went too far up or down
		if ((mPosY < 0) || (mPosY + CAR_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, wall[i]))
		{
			//Move back
			mPosY -= mVelY;
			mCollider.y = mPosY;
		}
	}
	if (abs(mVelX - mVelY) != 2)
	{
		mVelX = 0;
		mVelY = 0;
	}
}

void Car::render(LTexture& gDotTexture, SDL_Renderer& renderer)
{
	//Show the dot
	gDotTexture.render(renderer, mPosX, mPosY, NULL, angle);
}

int Car::getCarX() const
{
	return this->mPosX;
}

int Car::getCarY() const
{
	return this->mPosY;
}

void Car::tireSound()
{
	this->tire = Mix_LoadWAV("sounds/tires.wav");
	if (!tire)
	{
		std::cerr << "Sound cannot be loaded." << Mix_GetError << std::endl;
	}
}

void Car::engineSound()
{
	this->engine = Mix_LoadMUS("sounds/engine.mp3");
	if (!engine)
	{
		std::cerr << "Sound cannot be loaded." << Mix_GetError << std::endl;
	}
}

void Car::close()
{
	Mix_FreeChunk(tire);
	tire = NULL;
	Mix_FreeMusic(engine);
	engine = NULL;
	Mix_Quit();
}