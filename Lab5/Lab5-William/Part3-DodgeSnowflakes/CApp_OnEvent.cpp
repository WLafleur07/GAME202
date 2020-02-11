//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) 
{
	switch (Event->type)
	{
	case SDL_QUIT:
		Running = false;
	case SDL_KEYDOWN:
		switch (Event->key.keysym.sym) 
		{
		case SDLK_LEFT:
			runner.position.x -= 10;
			if (runner.position.x < 0)
			{
				runner.position.x = 0;
			}
			break;
		case SDLK_RIGHT:
			if(runner.position.x < window_w - runner.images[0].w)
			{
				runner.position.x += 10;
			}
			break;
		default:
			break;
		}
	}
}

//==============================================================================
