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
		allplayers[i].imagename = "Flying_Saucer.bmp";
        allplayers[i].loadPlayer(renderer);
        allplayers[i].position.x = rand() % (window_w);
        allplayers[i].position.y = rand() % (window_h);
        allplayers[i].velocity.x = 0;
        allplayers[i].velocity.y = 0;
        while (!allplayers[i].velocity.x && !allplayers[i].velocity.y) {
            allplayers[i].velocity.x = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
            allplayers[i].velocity.y = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
        }
    }
    console.imagename = "Space_Console_2.bmp";
    console.loadPlayer(renderer);
    console.velocity.x = 0;
    console.velocity.y = 0;
    console.position.x = 0;
    console.position.y = CONSOLE_START_Y;

	mars.imagename = "mars.bmp";
    mars.loadPlayer(renderer);
    mars.set_scroll_loc(0,0,window_w,CONSOLE_START_Y);
    return true;
}




//==============================================================================
