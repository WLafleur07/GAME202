//==============================================================================
// William Lafleur
// 4243260
// 2/4/2020
// Lab 4
//==============================================================================
#include "CApp.h"


void CApp::MoveSprites()
{
    
    int window_w = WINDOW_WIDTH;
    int window_h = WINDOW_HEIGHT;
    SDL_Rect *position, *velocity;

    /* Draw a gray background */
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        position = &positions[i];
        velocity = &velocities[i];

        position->x += velocity->x;
		position->y += velocity->y;

        /* Blit the sprite onto the screen */
		//if and else if statements to blit the 4 sprites onto the screen
		if (i == 0)
		{
			SDL_RenderCopy(renderer, sprite1, NULL, position);
		}
        
		else if (i == 1)
		{
			SDL_RenderCopy(renderer, sprite2, NULL, position);
		}

		else if (i == 2)
		{
			SDL_RenderCopy(renderer, sprite3, NULL, position);
		}

		else if (i == 3)
		{
			SDL_RenderCopy(renderer, sprite4, NULL, position);
		}
    }

	SDL_RenderPresent(renderer);
}


//==============================================================================
void CApp::OnLoop()
{
    MoveSprites();

	//handles joystick controls outside of event loop, because it stutters in event loop
	if (joy)
	{
		positions[0].y += SDL_JoystickGetAxis(joy, 1) / 6000;
		if (positions[0].y > WINDOW_HEIGHT - sprite_h)
			positions[0].y = WINDOW_HEIGHT - sprite_h;
		if (positions[0].y < 0)
			positions[0].y = 0;

		velocities[0].x = 0;
	}

	//mouse movement controls
	positions[1].y = mouse_y;
	velocities[1].x = 0;
	if (positions[1].y > WINDOW_HEIGHT - sprite_h)
	{
		positions[1].y = WINDOW_HEIGHT - sprite_h;
	}

}

//==============================================================================
