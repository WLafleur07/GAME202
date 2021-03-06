#include "CBalls.h"
#include <string>

using namespace std;

CBalls::CBalls() {

}

CBalls::CBalls(string s, int x = 0, int y = 0, int vx = 0, int vy = 0)
{
	imagename = s;
	position.x = x;
	position.y = y;
	velocity.x = vx;
	velocity.y = vy;
	loaded = false;
}

int CBalls::loadPlayer(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename.c_str());
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }
    position.w = temp->w;
    position.h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

void CBalls::display(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &position);

}

void CBalls::move(int &points)
{
    SDL_Rect *p;
    SDL_Rect *v;

    p = &position;
    v = &velocity;

    p->y += v->y;
    if ((p->y < 0) || (p->y >= (window_h - p->h)))
    {
       // v->y = 1;
        p->y += v->y;
    }

	if (p->y >= (window_h - p->h))
	{
		p->y = -5;
		//v->y = rand() % 6;
		p->x = rand() % (window_w);

		points++;
	}
}

