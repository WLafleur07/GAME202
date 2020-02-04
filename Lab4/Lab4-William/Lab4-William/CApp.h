//==============================================================================
// William Lafleur
// 4243260
// 2/4/2020
// Lab 4
//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include "SDL.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define NUM_SPRITES     4
#define MAX_SPEED       1

//==============================================================================
class CApp
{
private:
    bool Running;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *sprite1;
	SDL_Texture *sprite2;
	SDL_Texture *sprite3;
	SDL_Texture *sprite4;
    SDL_Rect positions[NUM_SPRITES];
    SDL_Rect velocities[NUM_SPRITES];
	SDL_Joystick *joy = nullptr;
    int sprite_w, sprite_h;
	int mouse_x, mouse_y;
	int i;

public:
    CApp();

    int OnExecute();

public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    int LoadSprite(char *file, SDL_Renderer* someRenderer, SDL_Texture* &someSprite);
    void MoveSprites();

    void OnCleanup();
};

//==============================================================================

#endif
