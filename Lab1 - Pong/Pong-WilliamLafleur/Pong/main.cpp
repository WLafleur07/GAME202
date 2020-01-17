/*
Name: William Lafleur
Prof: Majid Moghadam
Title of Program: Game Programming
Date: 1/13/2020
*/

#include <cstdlib>
#include <iostream>
//includes the SDL Library
#include "SDL.h"

using namespace std;

//defines the programs window size in pixels
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

//creates an SDL_Renderer pointer named rederer
SDL_Renderer *renderer;

//creates a bool as value true, will be used for main game loop
bool running = true;

//sets 5 rectangles for Player paddle, AI Paddle, Ball1 and the line
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect Ball1;
SDL_Rect Ball2;
SDL_Rect Line;

//the core of all event handling. A uninon of all event structures used in SDL
SDL_Event event;

//Mouse coordinates;
int mouse_x, mouse_y;

float speed_x, speed_y;
int direction[2] = { -1, 1 };

int speed2_x, speed2_y;

int playerScore = 0;
int AIScore = 0;

bool check_collision(SDL_Rect A, SDL_Rect B)
{
	//the sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	//if any of the sides from A are outside of B
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

	//if none of the sides from A are outside B
	return true;
}

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

	//Sets the starting X and Y coordinates of the Ball1, as well as height and width
	Ball1.x = rand() % (WINDOW_WIDTH /2 - 1);
	Ball1.y = rand() % WINDOW_HEIGHT;
	Ball1.w = 20;
	Ball1.h = 20;

	//Sets the starting X and Y coordinates of the Ball2, as well as height and width
	Ball2.x = rand() % (WINDOW_WIDTH /2 - 1);
	Ball2.y = rand() % WINDOW_HEIGHT;
	Ball2.w = 20;
	Ball2.h = 20;


	//sets the starting X and Y position of the line and the dimensions
	Line.x = 400;
	Line.y = 5;
	Line.w = 10;
	Line.h = 590;

	//speed variables
	speed_x = -1;
	speed_y = -1;

	speed2_x = -1;
	speed2_y = -1;
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


	//Ball1 goes out on sides left and right
	//reset to centre of screen
	if (Ball1.x < 0 || Ball1.x > WINDOW_WIDTH)
	{

		if (Ball1.x < 0)
		{
			cout << "Player Score:\t" << playerScore << endl;
			AIScore++;
			system("CLS");
			cout << "Player Score:\t" << playerScore << endl;
			cout << "AI Score:\t" << AIScore << endl;
		}
		
		if (Ball1.x > WINDOW_HEIGHT)
		{
			cout << "Player Score:\t" << playerScore << endl;
			playerScore++;
			system("CLS");
			cout << "Player Score:\t" << playerScore << endl;
			cout << "AI Score:\t" << AIScore << endl;
		}

		Ball1.x = WINDOW_WIDTH / 2;
		Ball1.y = WINDOW_HEIGHT / 2;
		//this expression produces random numbers -1, -2, 1 and 2
		speed_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed_y = (rand() % 2 + 1) * direction[rand() % 2];
	}
	
	if (Ball2.x < 0 || Ball2.x > WINDOW_WIDTH)
	{
		if (Ball2.x < 0)
		{
			cout << "Player Score:\t" << playerScore << endl;
			AIScore++;
			system("CLS");
			cout << "Player Score:\t" << playerScore << endl;
			cout << "AI Score:\t" << AIScore << endl;
		}

		if (Ball2.x > WINDOW_HEIGHT)
		{
			cout << "Player Score:\t" << playerScore << endl;
			playerScore++;
			system("CLS");
			cout << "Player Score:\t" << playerScore << endl;
			cout << "AI Score:\t" << AIScore << endl;
		}

		Ball2.x = WINDOW_WIDTH / 2;
		Ball2.y = WINDOW_HEIGHT / 2;
		//this expression produces random numbers -1, -2, 1 and 2
		speed2_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed2_y = (rand() % 2 + 1) * direction[rand() % 2];
	}

	if (Ball1.y < 0 || Ball1.y > (WINDOW_HEIGHT - Ball1.h))
	{
		speed_y = -speed_y;
	}

	if (Ball2.y < 0 || Ball2.y > (WINDOW_HEIGHT - Ball2.h))
	{
		speed2_y = -speed2_y;
	}

	if (PlayerPaddle.y < 0 || PlayerPaddle.y > WINDOW_HEIGHT - PlayerPaddle.h)
	{
		PlayerPaddle.y = 500;
	}


	if (Ball1.x > Ball2.x || Ball1.y > Ball2.y)
	{
		AIPaddle.y = Ball1.y - AIPaddle.h / 2 + Ball1.h / 2;
	}
	else
	{
		AIPaddle.y = Ball2.y - AIPaddle.h / 2 + Ball2.h / 2;
	}


	if (check_collision(Ball1, AIPaddle) || check_collision(Ball1, PlayerPaddle))
	{
		speed_x *= -1.15f;
	}

	if (check_collision(Ball2, AIPaddle) || check_collision(Ball2, PlayerPaddle))
	{
		speed2_x *= -1.15f;
	}

	Ball1.x += speed_x;
	Ball1.y += speed_y;

	//Velocity.y *= 1.15f;

	Ball2.x += speed2_x;
	Ball2.y += speed2_y;

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

	//sets the colour of the Ball1 and renders it
	SDL_SetRenderDrawColor(renderer, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
	SDL_RenderFillRect(renderer, &Ball1);

	SDL_SetRenderDrawColor(renderer, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
	SDL_RenderFillRect(renderer, &Ball2);

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