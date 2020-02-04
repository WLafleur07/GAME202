//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) 
{
	if (Event->type == SDL_QUIT || Event->type == SDL_KEYDOWN)
	{
		Running = false;
	}

	switch (Event->type)
	{

	case SDL_QUIT:
	case SDL_KEYDOWN:
		done = 1;
		break;

	case SDL_MOUSEMOTION:
		if (Event->type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);
		break;
	case SDL_MOUSEBUTTONDOWN:

		if (Event->button.button == 1)
		{
			positions[2].x = positions[1].x;
			positions[2].y = positions[1].y;
			velocities[2].x = -1;
		}

		break;
	case SDL_JOYBUTTONDOWN:
		if (Event->jbutton.which == 0 && Event->jbutton.button == 0) // Button 1 on 1st Joystick
		{
			positions[3].x = positions[0].x;
			positions[3].y = positions[0].y;
			velocities[3].x = -1;
		}
		else if (Event->jbutton.which == 0 && Event->jbutton.button == 1)  // Button 2 on 1st Joystick
		{
			done = 1;
		}
		break;
	}
}

//==============================================================================
