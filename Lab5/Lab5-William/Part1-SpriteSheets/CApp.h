//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include "SDL.h"
#include <string>
#include "CSpriteSheet.h"

using namespace std;

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480
#define NUM_SPRITES     10
#define MAX_SPEED       1

//==============================================================================
class CApp
{
private:
    bool            Running;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *sprite;
    SDL_Rect positions[NUM_SPRITES];
    SDL_Rect velocities[NUM_SPRITES];
    int sprite_w, sprite_h;
    CSpriteSheet runner;
    
public:
    CApp();

    int OnExecute();

public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    int LoadSprite(string filename);
    void MoveSprites();

    void OnCleanup();
};

//==============================================================================

#endif
