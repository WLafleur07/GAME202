//==============================================================================
// William Lafleur
// 4243260
// 2/4/2020
// Lab 4
//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) 
{
	
	switch (Event->type)
	{
	case SDL_QUIT:
	case SDL_KEYDOWN:
		Running = false;
		break;

		//case for mouse motion
	case SDL_MOUSEMOTION:
		if (Event->type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);
		break;

		//case for mouse button being pushed down
	case SDL_MOUSEBUTTONDOWN:

		//when mouse left-click is pressed, set cannonball position to the cannon postion, and give it a velocity of 1
		if (Event->button.button == 1)
		{
			positions[2].x = positions[1].x;
			positions[2].y = positions[1].y;
			velocities[2].x = -15;
			velocities[2].y = -15;
			
		}
		break;

		//case checking for joy button being pressed down
	case SDL_JOYBUTTONDOWN:
		//when button 0 is pressed on joystick, set fireball to the alien's position and give it a velocity of -1
		if (Event->jbutton.which == 0 && Event->jbutton.button == 0) // Button 1 on 1st Joystick
		{
			positions[3].x = positions[0].x;
			positions[3].y = positions[0].y;
			velocities[3].x = -15;
			velocities[3].y = -15;
		}
		break;
	}
}

//==============================================================================
