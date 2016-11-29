#include "myInts.h"




class myGame
{
private:
	SDL_Surface *screen;
	SDL_Surface *mouse;//I think mouse pics are 63x35
	SDL_Surface *background;
	bool gameRunning;
public:
	myGame();
	void gameLoad();
	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
	void draw_mouse (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination);
	bool checkCollision();
	void gameInit();
	void gameInput();
	void gameDraw();
	void gameUpdate();
	void gameCleanUp();
	bool runningState();
	
};

//The wall
SDL_Rect wall;
SDL_Rect wall2;
SDL_Rect wall3;



myGame::myGame()
{
}
void myGame::gameLoad()
{	
	IMG_INIT_JPG;
	IMG_INIT_PNG;
	mouse = IMG_Load("mouse.bmp");
	background = IMG_Load("background.jpg");
	SDL_SetColorKey(mouse,SDL_SRCCOLORKEY,SDL_MapRGB(mouse->format, 255, 0, 0));//argument to color key mouse to background
}

void myGame::gameInit()
{
	SDL_Init(SDL_INIT_EVERYTHING);//initializes all subsystems

	gameRunning = true;
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP, SDL_SWSURFACE);
	SDL_WM_SetCaption("Blah", NULL);
	//Set the wall
    wall.x = 300;
    wall.y = 40;
    wall.w = WALL_WIDTH;
    wall.h = 400;
	wall2.x = 100;
	wall2.y = 30;
	wall2.w = WALL_WIDTH;
	wall2.h = WALL_HEIGHT;
	
}

void myGame::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	SDL_BlitSurface(source,NULL,destination,&rect);

}



void myGame::draw_mouse (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect src;
	src.x = srcX;
	src.y = srcY;
	src.w = MOUSEWIDTH;
	src.h = MOUSEHEIGHT;

	SDL_Rect dst;
	dst.x = dstX;
	dst.y = dstY;
	dst.w = MOUSEWIDTH;
	dst.h = MOUSEHEIGHT;

	SDL_BlitSurface(source,&src,destination,&dst);
}

bool myGame::checkCollision()
{
	bool mouseCollide = false;
	//mouse sides
	int leftmouse = dstX;
	int rightmouse = dstX + MOUSEWIDTH;
	int topmouse = dstY;
	int bottommouse = dstY + MOUSEHEIGHT;
	//wall sides
	int leftwall = wall.x;
	int rightwall = wall.x +WALL_WIDTH;
	int topwall = wall.y;
	int bottomwall = wall.y +WALL_HEIGHT;

   //If any of the sides from A are outside of B
    if( bottommouse > topwall)
    {
       mouseCollide = true;
    }
	if (topmouse < bottomwall)
	{
		mouseCollide = true;
	}
    
    if( leftmouse > rightwall )
    {
        mouseCollide = true;
    }

	if( rightmouse < leftwall )
    {
        mouseCollide = true;
    }
	else 
	{
		mouseCollide = false;

	return mouseCollide;
}


void myGame::gameInput()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			gameRunning = false;
		}
	}
	//Get the keystates
    Uint8 *keystates = SDL_GetKeyState( NULL );

	//If buttons pressed these are the mouses velocities
    if( keystates[ SDLK_LEFT ] )
    {
		
        dstX -=6;
		if (checkCollision() == true)
		{
			dstX +=6;
		}
    }
	if(keystates[ SDLK_UP ])
	{
		dstY -=6;
		if (checkCollision() == true)
		{
			dstY +=6;
		}

	}
	
	if(keystates[ SDLK_RIGHT ], checkCollision())
	{
				
		dstX +=6;
		if (checkCollision() == true)
		{
			dstX -=6;
		}
	}
	if(keystates[ SDLK_DOWN ], checkCollision())
	{
		dstY +=6;
		if (checkCollision() == true)
		{
			dstY -=6;
		}
	}
	//collision checks
	if (dstX < 0)
	{
		dstX = 0;
	}
	if (dstY < 0)
	{
		dstY = 0;
	}
	if (dstX + MOUSEWIDTH > SCREEN_WIDTH)
	{
		dstX = SCREEN_WIDTH - MOUSEWIDTH;
	}
	if (dstY + MOUSEHEIGHT > SCREEN_HEIGHT)
	{
		dstY = SCREEN_HEIGHT - MOUSEHEIGHT;
	}
	//collision wall checks


    
}


void myGame::gameDraw()
{
	apply_surface(0,0,background,screen);
	SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0x255, 0x000, 0x000 ) );
	SDL_FillRect( screen, &wall2, SDL_MapRGB( screen->format, 0x255, 0x000, 0x000 ) );
	draw_mouse(srcX,srcY,dstX,dstY,MOUSEWIDTH,MOUSEHEIGHT, mouse, screen);


}
void myGame::gameUpdate()
{
	SDL_Flip(screen);
}
void myGame::gameCleanUp()
{
	SDL_Quit();
	exit(0);

}
bool myGame::runningState()
{
	return gameRunning;
}