//==============================================================================
#include "CApp.h"


void
CApp::MoveSprites()
{
    int i;

    /* Draw a gray background */

    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        allplayers[i].move();
        allplayers[i].display(renderer);
    }


}


//==============================================================================
void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    mars.move();
    mars.display(renderer);
    MoveSprites();
    console.display(renderer);

}

//==============================================================================
