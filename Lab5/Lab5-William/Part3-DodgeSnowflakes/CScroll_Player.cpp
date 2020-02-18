#include "CScroll_Player.h"

CScroll_Player::CScroll_Player()
{
    //ctor
}

CScroll_Player::~CScroll_Player()
{
    //dtor
}

void CScroll_Player::display(SDL_Renderer *prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);

}


int CScroll_Player::loadPlayer(SDL_Renderer *prenderer)
{
    int retval;

    retval = CBalls::loadPlayer(prenderer);
    destscr.x = 0;
    destscr.y = 0;
    destscr.h = window_h;
    destscr.w = window_w;
    velocity.x = 1;
    velocity.y = 0;
    return (retval);
}


//function to make the background texture scroll
void CScroll_Player::move(int &timesScroll)
{
    src.x += velocity.x;
    src.y += velocity.y;
    if (src.y >= position.h - window_h)
    {
        velocity.y = -velocity.y;
        src.y += velocity.y;
		
    }
    if (src.y < 0 )
    {
        velocity.y = -velocity.y;
        src.y += velocity.y;
    }
    if (src.x >= position.w - window_w)   // Assumes that image is greater than window width..
    {
        velocity.x = -velocity.x;
        src.x += velocity.x;
		timesScroll++;
    }
    if (src.x < 0)
    {
        velocity.x = -velocity.x;
        src.x += velocity.x;
    }

}
