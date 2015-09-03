#include "Button.h"


Button::Button(int width, int height)
{
	mPosition.x = 0;
	mPosition.y = 0;
	this->buttonWidth = width;
	this->buttonHeight = height;
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool Button::handleEvent(SDL_Event* e)
{
	bool isPressed = false;
	//If mouse event happened
	if ( e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + this->buttonWidth)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + this->buttonHeight)
		{
			inside = false;
		}

		//Mouse is outside button
		if (inside)
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEBUTTONUP:
				isPressed = true;
				break;
			}
		}
	}
	return isPressed;
}

bool Button::loadMedia(std::string path, SDL_Renderer &renderer)
{
	//Loading success flag
	bool success = true;

	//Load sprites
	if (!buttonBackground.loadFromFile(path, &renderer))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	return success;
}

void Button::render(SDL_Renderer &renderer)
{
	//Show current button sprite
	buttonBackground.render(renderer, mPosition.x, mPosition.y);
}
