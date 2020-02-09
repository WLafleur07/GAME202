//==============================================================================
// William Lafleur
// 4243260
// 2/4/2020
// Lab 4
//==============================================================================
#include "CApp.h"
#include <stdlib.h>
#include <time.h>
//==============================================================================
bool CApp::OnInit()
{
	//create a window with name Mini Game, place it in X = 100 and Y = 100
	window = SDL_CreateWindow("Mini Game", 100, 100,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	
	if (!window) {
		return false;
	}

	//sets rendering context to renderer 
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return false;
	}

	//function call to load sprite 1
	if (LoadSprite("alien.bmp", sprite1) < 0)
	{
		return false;
	}
	//sets starting x and y position of sprite1
	positions[0].x = 0;
	positions[0].y = 0;
	positions[0].w = sprite_w;
	positions[0].h = sprite_h;

	//function call to load sprite 2
	if (LoadSprite("cannon.bmp", sprite2) < 0)
	{
		return false;
	}
	//sets the starting x and y position of sprite2
	positions[1].x = WINDOW_WIDTH - sprite_w;
	positions[1].y = 0;
	positions[1].w = sprite_w;
	positions[1].h = sprite_h;

	//function call to load sprite 3
	if (LoadSprite("cannonball.bmp", sprite3) < 0)
	{
		return false;
	}
	//sets the starting x and y position of sprite3
	positions[2].x = WINDOW_WIDTH;
	positions[2].w = sprite_w;
	positions[2].h = sprite_h;

	//function call to load sprite 4
	if (LoadSprite("fireball.bmp", sprite4) < 0)
	{
		return false;
	}
	//sets the starting x and y position of sprite4
	positions[3].x = 0 - sprite_w;
	positions[3].y = 0 - sprite_h;
	positions[3].w = sprite_w;
	positions[3].h = sprite_h;

	//initializes the subsystem of JOYSTICK
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks() > 0)
	{
		joy = SDL_JoystickOpen(0);
	}

	return true;
}

//==============================================================================
