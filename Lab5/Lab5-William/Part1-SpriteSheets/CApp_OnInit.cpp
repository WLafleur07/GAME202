//==============================================================================
#include "CApp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//==============================================================================
bool CApp::OnInit()
{

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0)
    {
        return false;
    }
    window = SDL_CreateWindow("Basic SDL 2.0 Sprites",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
        return false;

    if (LoadSprite("cb.bmp") < 0)
        return false;

    srand(time(NULL));
    for (int i = 0; i < NUM_SPRITES; ++i) {
        positions[i].x = rand() % (WINDOW_WIDTH - sprite_w);
        positions[i].y = rand() % (WINDOW_HEIGHT - sprite_h);
        positions[i].w = sprite_w;
        positions[i].h = sprite_h;
        velocities[i].x = 0;
        velocities[i].y = 0;
        while (!velocities[i].x && !velocities[i].y) {
            velocities[i].x = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
            velocities[i].y = (rand() % (MAX_SPEED * 2 + 1)) - MAX_SPEED;
        }
    }

    runner.set_sheet("mushroom_fellow_945x690px.bmp");
    if (runner.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    runner.config_sheet(14,0,0,189,230,5,3,0);
	runner.position.h = runner.images[0].h;
	runner.position.w = runner.images[0].w;
	runner.position.x = 50;
	runner.position.y = 10;
    return true;
}

//==============================================================================
