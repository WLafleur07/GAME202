/*
Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely.
*/
/* Simple program:  Move N sprites around on the screen as fast as possible */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"

#ifdef __NDS__
#define WINDOW_WIDTH    256
#define WINDOW_HEIGHT   (2*192)
#else
#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   384
#endif
//#define NUM_SPRITES     2
#define MAX_SPEED       1
#define WW2 (WINDOW_WIDTH>>1)
#define WH2 (WINDOW_HEIGHT>>1)

static SDL_Texture *sprite1;
static SDL_Texture *sprite2;
static SDL_Texture *sprite3;
static SDL_Texture *sprite4;


//static int sprite_w2, sprite_h2;
//static int sprite_w3, sprite_h3;

SDL_Joystick *joy = nullptr;
int mouse_x, mouse_y;

enum SPRITES
{
	CANNON,
	ALIEN,
	CANNONBALL,
	FIREBALL,
	
	MAX_SPRITES
};

static int sprite_w, sprite_h;

static SDL_Rect positions[MAX_SPRITES];
static SDL_Rect velocities[MAX_SPRITES];

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void quit(int rc)
{
	exit(rc);
}

int LoadSprite(char *file, SDL_Renderer *renderer, SDL_Texture* &someSprite)
{
	SDL_Surface *temp;

	/* Load the sprite image */
	temp = SDL_LoadBMP(file);
	if (temp == NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
		return (-1);
	}
	sprite_w = temp->w;
	sprite_h = temp->h;

	/* Set transparent pixel as the pixel at (0,0) */
	if (temp->format->palette)
	{
		SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *)temp->pixels);
	}
	else
	{
		switch (temp->format->BitsPerPixel)
		{
		case 15:
			SDL_SetColorKey(temp, SDL_TRUE,
				(*(Uint16 *)temp->pixels) & 0x00007FFF);
			break;
		case 16:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *)temp->pixels);
			break;
		case 24:
			SDL_SetColorKey(temp, SDL_TRUE,
				(*(Uint32 *)temp->pixels) & 0x00FFFFFF);
			break;
		case 32:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *)temp->pixels);
			break;
		}
	}

	/* Create textures from the image */
	someSprite = SDL_CreateTextureFromSurface(renderer, temp);
	if (!someSprite)
	{
		fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
		SDL_FreeSurface(temp);
		return (-1);
	}
	SDL_FreeSurface(temp);

	/* We're ready to roll. :) */
	return (0);
}

void MoveSprites(SDL_Window * window, SDL_Renderer * renderer)
{
	int i;
	int window_w = WINDOW_WIDTH;
	int window_h = WINDOW_HEIGHT;
	SDL_Rect *position, *velocity;

	/* Draw a gray background */
	SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
	SDL_RenderClear(renderer);

	/* Move the sprite, bounce at the wall, and draw */
	for (i = 0; i < MAX_SPRITES; ++i)
	{

		position = &positions[i];
		velocity = &velocities[i];
		if (i != 0)
		{
			position->x += velocity->x;
			if ((position->x < 0) || (position->x >= (window_w - sprite_w)))
			{
				velocity->x = -velocity->x;
				position->x += velocity->x;
			}
			position->y += velocity->y;
			if ((position->y < 0) || (position->y >= (window_h - sprite_h)))
			{
				velocity->y = -velocity->y;
				position->y += velocity->y;
			}
		}
		//Blit the sprite onto the screen 
		if (i == 0)
		{
			SDL_RenderCopy(renderer, sprite1, NULL, position);
		}
		if (i == 1)
		{
			SDL_RenderCopy(renderer, sprite2, NULL, position);
		}
		if (i == 2)
		{
			SDL_RenderCopy(renderer, sprite3, NULL, position);
		}
		if (i == 3)
		{
			SDL_RenderCopy(renderer, sprite4, NULL, position);
		}
	}

	/* Update the screen! */
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int i, done;
	SDL_Event event;


	window = SDL_CreateWindow("Mini Game", 100, 100,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		quit(2);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		quit(2);
	}

	if (LoadSprite("alien.bmp", renderer, sprite1) < 0)
	{
		quit(2);
	}

	if (LoadSprite("cannon.bmp", renderer, sprite2) < 0)
	{
		quit(2);
	}

	if (LoadSprite("cannonball.bmp", renderer, sprite3) < 0)
	{
		quit(2);
	}

	if (LoadSprite("fireball.bmp", renderer, sprite4) < 0)
	{
		quit(2);
	}

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks() > 0)
	{
		joy = SDL_JoystickOpen(0);

	}
	
	positions[0].x = 0;
	positions[0].y = 0;
	positions[0].w = sprite_w;
	positions[0].h = sprite_h;

	positions[1].x = WINDOW_WIDTH - sprite_w;
	positions[1].y = 0;
	positions[1].w = sprite_w;
	positions[1].h = sprite_h;

	positions[2].x = WINDOW_WIDTH;
	positions[2].w = sprite_w;
	positions[2].h = sprite_h;

	positions[3].x = 0 - sprite_w;
	positions[3].y = 0 - sprite_h;
	positions[3].w = sprite_w;
	positions[3].h = sprite_h;

	/* Initialize the sprite positions */
	srand(time(NULL));
	for (i = 0; i < MAX_SPRITES; ++i)
	{
		/*positions[i].x = rand() % (WINDOW_WIDTH - sprite_w);
		positions[i].y = rand() % (WINDOW_HEIGHT - sprite_h);
		positions[i].w = sprite_w;
		positions[i].h = sprite_h;*/
		velocities[i].x = 0;
		velocities[i].y = 0;

		/*while (!velocities[i].x && !velocities[i].y)
		{
			velocities[i].x = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
			velocities[i].y = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
		}*/
	}

	/* Main render loop */
	done = 0;
	while (!done)
	{
		/* Check for events */
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEMOTION)
				SDL_GetMouseState(&mouse_x, &mouse_y);

			switch (event.type)
			{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				done = 1;
				break;

			case SDL_MOUSEMOTION:
				/*printf("Mouse moved by %d,%d to (%d,%d)\n",
					event.motion.xrel, event.motion.yrel,
					event.motion.x, event.motion.y);*/

					//Track mouse movement
				if (event.type == SDL_MOUSEMOTION)
					SDL_GetMouseState(&mouse_x, &mouse_y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				//printf("Mouse button %d pressed at (%d,%d)\n",
					//event.button.button, event.button.x, event.button.y);
				//printf("Mouse button pressed \n");

				if (event.button.button == 1)
				{
					positions[2].x = positions[1].x;
					positions[2].y = positions[1].y;
					velocities[2].x = -1;
				}

				break;
			case SDL_JOYBUTTONDOWN:
				if (event.jbutton.which == 0 && event.jbutton.button == 0) // Button 1 on 1st Joystick
				{
					positions[3].x = positions[0].x;	
					positions[3].y = positions[0].y;
					velocities[3].x = -1;
				}
				else if (event.jbutton.which == 0 && event.jbutton.button == 1)  // Button 2 on 1st Joystick
				{
					done = 1;
				}
				break;
				/*
				case SDL_JOYAXISMOTION:
				switch(event.jaxis.which)
				{
				case 0:
				positions[0].x += event.jaxis.value / 6000;
				if (positions[0].x>WINDOW_WIDTH-sprite_w)
				positions[0].x = WINDOW_WIDTH-sprite_w;
				if (positions[0].x< 0)
				positions[0].x = 0;
				break;
				case 1:
				positions[0].y += event.jaxis.value / 6000;
				if (positions[0].y>WINDOW_HEIGHT-sprite_h)
				positions[0].y = WINDOW_HEIGHT-sprite_h;
				if (positions[0].y< 0)
				positions[0].y = 0;
				break;
				}
				break;
				*/
			}

		}
		if (joy)
		{

			//positions[0].x += SDL_JoystickGetAxis(joy, 0) / 6000;
			positions[0].y += SDL_JoystickGetAxis(joy, 1) / 6000;
			/*if (positions[0].x > WINDOW_WIDTH - sprite_w)
				positions[0].x = WINDOW_WIDTH - sprite_w;
			if (positions[0].x < 0)
				positions[0].x = 0;*/
			if (positions[0].y > WINDOW_HEIGHT - sprite_h)
				positions[0].y = WINDOW_HEIGHT - sprite_h;
			if (positions[0].y < 0)
				positions[0].y = 0;

			velocities[0].x = 0;

		}

		positions[1].y = mouse_y;
		velocities[1].x = 0;
		if (positions[1].y > WINDOW_HEIGHT - sprite_h)
		{
			positions[1].y = WINDOW_HEIGHT - sprite_h;
		}
		//positions[1].x = mouse_x;

		MoveSprites(window, renderer);
	//	MoveSprites(window, renderer, sprite2);
		SDL_Delay(10);
	}

	//if ()

	quit(0);

	return 0;
}

