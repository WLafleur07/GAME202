//==============================================================================
#include "CApp.h"


void CApp::MoveSprites()
{
    int i;

    /* Draw a gray background */

    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        allplayers[i].move();
        allplayers[i].display(renderer);

		if (checkCollision(allplayers[i].position, runner.position) == true)
		{
			allplayers[i].position.y = -5;
		}
    }


}


//==============================================================================
void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    
    MoveSprites();

	static Uint32 cnt = 0;

	
	if (cnt % 2 == 0)
		runner.play(renderer, &runner.position, true);
	else
		runner.play(renderer, &runner.position, false);
	cnt++;
   
	
	

}

//==============================================================================
