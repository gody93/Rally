#pragma once
#include "Globals.h"
#include "LTexture.h"

class Button
{
public:
	//Initializes internal variables
	Button(int width, int height);

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	bool handleEvent(SDL_Event* e);

	void render(SDL_Renderer &renderer);

	bool loadMedia(std::string path, SDL_Renderer &renderer);
private:
	int buttonWidth;
	int buttonHeight;

	//Top left position
	SDL_Point mPosition;

	LTexture buttonBackground;

};
