//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include "mywindow.h"
#include "CBalls.h"
#include "CSpriteSheet.h"
#include "CScroll_Player.h"


#define TICK_INTERVAL    10
#define NUM_SPRITES     10
#define MAX_SPEED       1

//==============================================================================
class CApp
{
private:
    bool Running;

	
	int runnerHealth = 100;
	int score = 0;
	int scrollNum = 0;
	

    Uint32 next_time;
    SDL_Window *window;
    SDL_Renderer *renderer;
	CBalls allBalls[NUM_SPRITES];
	CSpriteSheet runner;
	CScroll_Player landscape;

public:
    CApp();
    Uint32 time_left(void);
    int OnExecute();

public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    int LoadSprite(char *file, SDL_Texture* &psprite, SDL_Rect *prect);
    void MoveSprites();

    void OnCleanup();

	bool checkCollision(SDL_Rect A, SDL_Rect B);

	void printScore();
	void printRunnerHealth();
	void printScrollNumber();
	void clearScreen();

};

//==============================================================================

#endif
