//==============================================================================
#include "CApp.h"
#include <stdlib.h>
#include <time.h>
//==============================================================================
bool CApp::OnInit()
{

    int i;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0)
    {
        return false;
    }
    window = SDL_CreateWindow("Basic SDL 2.0 Scrolling",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    srand(time(NULL));

    for (i = 0; i < NUM_SPRITES; ++i) {
		allBalls[i] = CBalls("ballAttack.bmp", rand() % (window_w)-allBalls->position.w, rand() % -10, 0, 0);
		allBalls[i].loadPlayer(renderer);
		allBalls[i].position.w = 30;
		allBalls[i].position.h = 30;
	
        while (!allBalls[i].velocity.x && !allBalls[i].velocity.y)
		{
			allBalls[i].velocity.y = rand() % 10;
        }
    }
    
	runner.set_sheet("walksequence_spritesheet-512.bmp");
	if (runner.load_sheet(renderer) != 0)
	{
		printf("Bad load of runner animation file\n");
	}
	runner.config_sheet(30, 0, 0, 85, 105, 6, 5, 0);
	runner.position.h = runner.images[0].h;
	runner.position.w = runner.images[0].w;
	runner.position.x = window_w / 2;
	runner.position.y = window_h - runner.images[0].h;

	landscape.imagename = "101186.bmp";
	landscape.loadPlayer(renderer);
	landscape.set_scroll_loc(0, 500, window_w, window_h);

	return true;
}
    





//==============================================================================
