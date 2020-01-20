#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//defines max sprites to a number of 6
#define NUM_SPRITES     6
#define MAX_SPEED       1

SDL_Texture *sprite;
SDL_Rect positions[NUM_SPRITES];
SDL_Rect velocities[NUM_SPRITES];
int sprite_w, sprite_h;


int LoadSprite(char *file, SDL_Renderer *renderer)
{
	SDL_Surface *temp;

	// Load the sprite image
	temp = SDL_LoadBMP(file);
	if (temp == NULL) {
		fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
		return (-1);
	}

	//sets with and height of sprites
	sprite_w = temp->w;
	sprite_h = temp->h;

	// Set transparent pixel as the pixel at (0,0)
	if (temp->format->palette) {
		SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *)temp->pixels);
	}
	else {
		switch (temp->format->BitsPerPixel) {
		case 15:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint16 *)temp->pixels) & 0x00007FFF);
			break;
		case 16:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *)temp->pixels);
			break;
		case 24:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint32 *)temp->pixels) & 0x00FFFFFF);
			break;
		case 32:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *)temp->pixels);
			break;
		}
	}

	// Create textures from the image
	sprite = SDL_CreateTextureFromSurface(renderer, temp);
	if (!sprite) {
		fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
		SDL_FreeSurface(temp);
		return (-1);
	}
	SDL_FreeSurface(temp);

	return (0);
}

void MoveSprites(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * sprite)
{
	int i;
	int window_w = WINDOW_WIDTH;
	int window_h = WINDOW_HEIGHT;
	SDL_Rect *position, *velocity;

	// Draw a gray background
	SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
	SDL_RenderClear(renderer);



	// Move the sprite, bounce at the wall, and draw
	for (i = 0; i < NUM_SPRITES; ++i) {
		position = &positions[i];
		velocity = &velocities[i];
		position->x += velocity->x;
		if ((position->x < 0) || (position->x >= (window_w - sprite_w))) {
			velocity->x = -velocity->x;
			position->x += velocity->x;
		}
		position->y += velocity->y;
		if ((position->y < 0) || (position->y >= (window_h - sprite_h))) {
			velocity->y = -velocity->y;
			position->y += velocity->y;
		}

		// Blit the sprite onto the screen
		SDL_RenderCopy(renderer, sprite, NULL, position);
	}


	// Update the screen!
	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int i, done;
	SDL_Event event;

	window = SDL_CreateWindow("Basic SDL Sprites",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return false;
	}

	if (LoadSprite("hts.bmp", renderer) < 0) {
		return false;
	}

	// Initialize the sprite positions
	srand(time(NULL));
	for (i = 0; i < NUM_SPRITES; ++i) {

		//initializes a random position between 0 and 799 - the sprites width so it does not go off screen
		positions[i].x = rand() % (WINDOW_WIDTH - sprite_w);
		positions[i].y = rand() % (WINDOW_HEIGHT - sprite_h);
		positions[i].w = sprite_w;
		positions[i].h = sprite_h;
		velocities[i].x = 0;
		velocities[i].y = 0;

		//first sprite(index 0) moves horizontally and second sprite(index 1) to move vertically
		velocities[0].x = 1;
		velocities[0].y = 0;
		velocities[1].x = 0;
		velocities[1].y = 1;

		while (!velocities[i].x && !velocities[i].y) {
			//sets a random velocity to give x and y speeds of -1, 0 or 1
			velocities[i].x = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
			velocities[i].y = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
		}

	}

	// Main render loop
	done = 0;
	while (!done) {//game loop
		// Check for events
		while (SDL_PollEvent(&event)) {//event loop
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
				done = 1;
			}
		}
		MoveSprites(window, renderer, sprite);

		//if index 0 X is greater than 0, increase by 1 through each iteration of loop
		if (velocities[0].x > 0)
		{
			velocities[0].x++;
		}

		//if index 1 y is greater than 0, increase by 1 through each iteration of loop
		if (velocities[1].y > 0)
		{
			velocities[1].y++;
		}

		//setting a delay of 20
		SDL_Delay(20);
	}

	SDL_Quit();

	return true;
}
