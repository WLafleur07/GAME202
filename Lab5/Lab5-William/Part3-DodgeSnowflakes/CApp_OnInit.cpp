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
		allplayers[i].imagename = "snowflake.bmp";
        allplayers[i].loadPlayer(renderer);
        allplayers[i].position.x = rand() % (window_w);
        allplayers[i].position.y = -5;
        allplayers[i].velocity.x = 0;
        allplayers[i].velocity.y = 0;
        while (!allplayers[i].velocity.x && !allplayers[i].velocity.y) {
            //allplayers[i].velocity.x = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
			allplayers[i].velocity.y = rand() % 6;
			if (allplayers[i].velocity.y <= 3)
			{
				allplayers[i].velocity.y = 4;
			}
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


	return true;
}
    





//==============================================================================
