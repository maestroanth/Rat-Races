
void myGame::setMouseClips()
{
    //Clip the sprites
    clipsRight[ 0 ].x = 0;
    clipsRight[ 0 ].y = 0;
    clipsRight[ 0 ].w = MOUSEWIDTH;
    clipsRight[ 0 ].h = MOUSEHEIGHT;


    clipsRight[ 1 ].x = MOUSEWIDTH;
    clipsRight[ 1 ].y = 0;
    clipsRight[ 1 ].w = MOUSEWIDTH;
    clipsRight[ 1 ].h = MOUSEHEIGHT;

    clipsRight[ 2 ].x = MOUSEWIDTH * 2;
    clipsRight[ 2 ].y = 0;
    clipsRight[ 2 ].w = MOUSEWIDTH;
    clipsRight[ 2 ].h = MOUSEHEIGHT;

	clipsRight[ 3 ].x = MOUSEWIDTH * 3;
    clipsRight[ 3 ].y = 0;
    clipsRight[ 3 ].w = MOUSEWIDTH;
    clipsRight[ 3 ].h = MOUSEHEIGHT;

	clipsLeft[ 0 ].x = 0;
    clipsLeft[ 0 ].y = MOUSEHEIGHT;
    clipsLeft[ 0 ].w = MOUSEWIDTH;
    clipsLeft[ 0 ].h = MOUSEHEIGHT;


    clipsLeft[ 1 ].x = MOUSEWIDTH;
    clipsLeft[ 1 ].y = MOUSEHEIGHT;
    clipsLeft[ 1 ].w = MOUSEWIDTH;
    clipsLeft[ 1 ].h = MOUSEHEIGHT;

    clipsLeft[ 2 ].x = MOUSEWIDTH * 2;
    clipsLeft[ 2 ].y = MOUSEHEIGHT;
    clipsLeft[ 2 ].w = MOUSEWIDTH;
    clipsLeft[ 2 ].h = MOUSEHEIGHT;

	clipsLeft[ 3 ].x = MOUSEWIDTH * 3;
    clipsLeft[ 3 ].y = MOUSEHEIGHT;
    clipsLeft[ 3 ].w = MOUSEWIDTH;
    clipsLeft[ 3 ].h = MOUSEHEIGHT;

	clipsDown[ 0 ].x = 0;
    clipsDown[ 0 ].y = MOUSEHEIGHT *2;
    clipsDown[ 0 ].w = MOUSEWIDTH;
    clipsDown[ 0 ].h = MOUSEHEIGHT;


    clipsDown[ 1 ].x = MOUSEWIDTH;
    clipsDown[ 1 ].y = MOUSEHEIGHT *2;
    clipsDown[ 1 ].w = MOUSEWIDTH;
    clipsDown[ 1 ].h = MOUSEHEIGHT;

    clipsDown[ 2 ].x = MOUSEWIDTH * 2;
    clipsDown[ 2 ].y = MOUSEHEIGHT *2;
    clipsDown[ 2 ].w = MOUSEWIDTH;
    clipsDown[ 2 ].h = MOUSEHEIGHT;

	clipsDown[ 3 ].x = MOUSEWIDTH * 3;
    clipsDown[ 3 ].y = MOUSEHEIGHT *2;
    clipsDown[ 3 ].w = MOUSEWIDTH;
    clipsDown[ 3 ].h = MOUSEHEIGHT;

	clipsUp[ 0 ].x = 0;
    clipsUp[ 0 ].y = MOUSEHEIGHT * 3;
    clipsUp[ 0 ].w = MOUSEWIDTH;
    clipsUp[ 0 ].h = MOUSEHEIGHT;


    clipsUp[ 1 ].x = MOUSEWIDTH;
    clipsUp[ 1 ].y = MOUSEHEIGHT * 3;
    clipsUp[ 1 ].w = MOUSEWIDTH;
    clipsUp[ 1 ].h = MOUSEHEIGHT;

    clipsUp[ 2 ].x = MOUSEWIDTH * 2;
    clipsUp[ 2 ].y = MOUSEHEIGHT * 3;
    clipsUp[ 2 ].w = MOUSEWIDTH;
    clipsUp[ 2 ].h = MOUSEHEIGHT;

	clipsUp[ 3 ].x = MOUSEWIDTH * 3;
    clipsUp[ 3 ].y = MOUSEHEIGHT * 3;
    clipsUp[ 3 ].w = MOUSEWIDTH;
    clipsUp[ 3 ].h = MOUSEHEIGHT;




}

Uint32 myGame::AnimationTimer(void)
{
	static Uint32 next_time = 0;
	Uint32 now = SDL_GetTicks();
	if (next_time < now)
	{
		next_time = now + MOUSEMOVE;
		mouseframe ++;
		return(0);
	}
	return(next_time-now);
}