/*
Name: William Lafleur
Prof: Majid Moghadam
Title of Program: Game Programming
Date: 1/13/2020
*/

#include <cstdio>
#include <cstdlib>
//includes the SDL Library
#include "SDL.h"

//defines the programs window size in pixels
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

//creates an SDL_Renderer pointer named rederer
SDL_Renderer *renderer;

//creates a bool as value true, will be used for main game loop
bool running = true;

//sets 4 rectangles for Player paddle, AI Paddle, ball and the line
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball;
SDL_Rect Line;

//the core of all event handling. A uninon of all event structures used in SDL
SDL_Event event;

//Mouse coordinates;
int mouse_x, mouse_y;

int speed_x, speed_y;
int direction[2] = { -1, 1 };

/*
Purpose of LoadGame Function: Sets starting location of the window, and objects within the window. Has two error checks, if not true, they return
*/
void LoadGame()
{
	//Creates a SDL_Window pointer named window
	SDL_Window *window;

	//
	window = SDL_CreateWindow("Basic SDL Sprites",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		return;
	}

	//function to create a 2D rendering context for a window
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return;
	}

	//Sets the starting location of the paddle on the X and Y axis. Sets the Height and width of the paddle as well
	PlayerPaddle.x = 20;
	PlayerPaddle.y = 250;
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 20;

	//Sets the starting X and Y coordinates of the AI Paddle, as well as the height and width
	AIPaddle.x = 760;
	AIPaddle.y = 250;
	AIPaddle.h = 100;
	AIPaddle.w = 20;

	//Sets the starting X and Y coordinates of the ball, as well as height and width
	Ball.x = 370;
	Ball.y = 290;
	Ball.w = 20;
	Ball.h = 20;

	//sets the starting X and Y position of the line and the dimensions
	Line.x = 400;
	Line.y = 5;
	Line.w = 10;
	Line.h = 590;

	//speed variables
	speed_x = -1;
	speed_y = -1;
}

/*
Purpose of the Input function: a function to handle user input
*/
void Input() 
{
	//Queuing events
	while (SDL_PollEvent(&event)) {

		//Track mouse movement
		if (event.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);

		//clicking 'x' or pressing F4
		if (event.type == SDL_QUIT)
			running = false;

		//Pressing a key
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{

				//Pressing ESC exits from the game
			case SDLK_ESCAPE:
				running = false;
				break;
			}
	}
}

/*
Purpose of the Update function:
*/
void Update()
{
	PlayerPaddle.y = mouse_y;


	//ball goes out on sides left and right
	//reset to centre of screen
	if (Ball.x < 0 || Ball.x > WINDOW_WIDTH)
	{
		Ball.x = WINDOW_WIDTH / 2;
		Ball.y = WINDOW_HEIGHT / 2;
		//this expression produces random numbers -1, -2, 1 and 2
		speed_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed_y = (rand() % 2 + 1) * direction[rand() % 2];
	}

	Ball.x += speed_x;
	Ball.y += speed_y;

	SDL_Delay(10);
}

/*
Purpose of the DrawScreen function: draws all the objects with their respective colours on screen
*/
void DrawScreen()
{
	//a function the clears the current rendering target. Function takes in renderer pointer as paramter
	SDL_RenderClear(renderer);

	//sets the background dimensions to be coloured and fills it with a colour
	SDL_Rect background = { 0, 0, 800, 600 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);

	//sets the rendered colour of Player paddle and AI Paddle
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &PlayerPaddle);
	SDL_RenderFillRect(renderer, &AIPaddle);

	//sets the colour of the ball
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Ball);

	//sets the colour of the line
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Line);

	//function to update the screen with any rendering performed since the previous call
	SDL_RenderPresent(renderer);
}

/*
Purpose of the Quit function: Allows user to close the program
*/
void Quit()
{
	//calls the SDL Quit function
	SDL_Quit();
}

/*
Purpose of the Main function: runs the main function, which contains main game loop
*/
int main(int argc, char *argv[])
{
	//calls the load game function, which will initialize objects and their starting positions/dimensions
	LoadGame();

	//Main game loop, loops 60 times a second. Continues to run as long is it is equal to true
	while (running == true)
	{
		Input();
		Update();
		DrawScreen();
	}

	//calls the Quit function and terminates the program
	Quit();

	return 0;
}