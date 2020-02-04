//==============================================================================
#include "CApp.h"
#include <stdlib.h>
#include <time.h>
//==============================================================================
bool CApp::OnInit()
{

	window = SDL_CreateWindow("Mini Game", 100, 100,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	
	if (!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		SDL_Quit();
	}

	if (LoadSprite("alien.bmp", renderer, sprite1) < 0)
	{
		return false;
	}

	positions[0].x = 0;
	positions[0].y = 0;
	positions[0].w = sprite_w;
	positions[0].h = sprite_h;

	if (LoadSprite("cannon.bmp", renderer, sprite2) < 0)
	{
		return false;
	}

	positions[1].x = WINDOW_WIDTH - sprite_w;
	positions[1].y = 0;
	positions[1].w = sprite_w;
	positions[1].h = sprite_h;

	if (LoadSprite("cannonball.bmp", renderer, sprite3) < 0)
	{
		return false;
	}

	positions[2].x = WINDOW_WIDTH;
	positions[2].w = sprite_w;
	positions[2].h = sprite_h;

	if (LoadSprite("fireball.bmp", renderer, sprite4) < 0)
	{
		return false;
	}

	positions[3].x = 0 - sprite_w;
	positions[3].y = 0 - sprite_h;
	positions[3].w = sprite_w;
	positions[3].h = sprite_h;

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks() > 0)
	{
		joy = SDL_JoystickOpen(0);
	}

	/* Initialize the sprite positions */
	srand(time(NULL));
	for (i = 0; i < NUM_SPRITES; ++i)
	{
		velocities[i].x = 0;
		velocities[i].y = 0;

	}

	return true;
}

//==============================================================================
