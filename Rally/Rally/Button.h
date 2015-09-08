#pragma once
#include "Globals.h"
#include "LTexture.h"

class Button
{
public:
	//Initializes internal variables
	Button(int,int,int,int);
	Button();
	~Button();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	bool handleEvent(SDL_Event* e);

	//Renders the button background
	void render(SDL_Renderer &renderer);

	//Loads button media
	bool loadMedia(std::string path, SDL_Renderer &renderer);
	
	//Frees texture backgrounds
	void free();
private:
	int buttonWidth;
	int buttonHeight;

	//Top left position
	SDL_Point mPosition;

	LTexture buttonBackground;

};
