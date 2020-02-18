//==============================================================================
#include "CApp.h"


void CApp::MoveSprites()
{
    int i;

    /* Draw a gray background */
	landscape.move(scrollNum);
	landscape.display(renderer);
    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
		allBalls[i].move(score);
		allBalls[i].display(renderer);

		if (checkCollision(allBalls[i].position, runner.position) == true)
		{
			allBalls[i].position.y = -5;
			allBalls[i].position.x = rand() % (window_w)-allBalls->position.w;

			score += -2;
			runnerHealth += -2;

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
