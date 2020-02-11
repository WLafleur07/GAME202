//==============================================================================
#include "CApp.h"


void
CApp::MoveSprites()
{
    int i;
    int window_w = WINDOW_WIDTH;
    int window_h = WINDOW_HEIGHT;
    SDL_Rect *position, *velocity;

    /* Draw a gray background */
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES ; ++i)
    {
        position = &positions[i];
        velocity = &velocities[i];
        position->x += velocity->x;
        if ((position->x < 0) || (position->x >= (window_w - sprite_w)))
        {
            velocity->x = -velocity->x;
            position->x += velocity->x;
        }
        position->y += velocity->y;
        if ((position->y < 0) || (position->y >= (window_h - sprite_h)))
        {
            velocity->y = -velocity->y;
            position->y += velocity->y;
        }

        /* Blit the sprite onto the screen */
        SDL_RenderCopy(renderer, sprite, NULL, position);
    }


}


//==============================================================================
void CApp::OnLoop()
{
    static Uint32 cnt = 0;

    MoveSprites();
    if (cnt % 2 == 0)
       runner.play(renderer,&runner.position,true);
    else
        runner.play(renderer,&runner.position,false);
    cnt++;


}

//==============================================================================
