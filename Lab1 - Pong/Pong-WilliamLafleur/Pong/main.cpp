/*
Name: William Lafleur
Prof: Majid Moghadam
Title of Program: Game Programming
Date: 1/13/2020
*/

//includes the SDL Library
#include "SDL.h"

//defines the programs window size in pixels
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

//creates an SDL_Renderer pointer named rederer
SDL_Renderer *renderer;

//creates a bool as value true, will be used for main game loop
bool running = true;

//sets 3 ractangles for Player paddle, AI Paddle, and the ball
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball;

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

	//
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
}

/*
Purpose of the Input function: a function to take in user input
*/
void Input() {

}

/*
Purpose of the Update function:
*/
void Update()
{

}

/*
Purpose of the DrawScreen function:
*/
void DrawScreen()
{
	//a function the clears the current rendering target. Function takes in renderer pointer as paramter
	SDL_RenderClear(renderer);

	//defines the rectangualr area of the screen
	SDL_Rect background = { 0, 0, 800, 600 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);

	//
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &PlayerPaddle);
	SDL_RenderFillRect(renderer, &AIPaddle);

	//
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Ball);

	//
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
	//
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