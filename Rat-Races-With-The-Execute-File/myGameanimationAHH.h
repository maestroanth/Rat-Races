#include "myInts.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
//i mixed all music/sounds
//copyright notice I did compose the wave file RatRace and self-recorded the foxlogo theme via piano, 
//you can take my bump sound

//http://www.youtube.com/watch?v=94pPyuS1E_M&feature=results_video&playnext=1&list=PL7AAC186E33109DB1 and do this this after lazy foo's first two tutorials
//http://www.kekkai.org/roger/sdl/mixer/
//http://lazyfoo.net/SDL_tutorials/



class myGame
{
private:
	//video
	SDL_Surface *screen;
	SDL_Surface *mouse;//I think mouse pics are 63x35
	SDL_Surface *background;
	SDL_Surface *cheese;
	SDL_Surface *win;
	SDL_Surface *lose;
	SDL_Surface *cat;
	//music
	Mix_Music *music;
	Mix_Music *foxlogo;
	Mix_Music *loseMusic;
	Mix_Chunk *bump;
	//timer stuff
	TTF_Font *font;
	SDL_Surface *startStop;
	SDL_Surface *seconds;
	bool gameRunning;
	//cheese coordinates
	int cheeseX;
	int cheeseY;
	
public:
	
	myGame();
	void gameLoad();
	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect &clips);
	void draw_mouse (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination);
	void draw_cat (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination);
	bool checkCollision(int i);
	void mouseMotion();
	void gameInit();
	void gameInput();
	void gameDraw();
	void gameUpdate();
	void gameCleanUp();
	bool runningState();
	void musicDone();
	void set_clips();
	bool checkCheeseColl(int cheeseX, int cheeseY);//i'm working on localizing these parameters for an exact cheese destination per maze
	//i can also try to start adding more cheeses and stuff too
	//my mazes that work
	void maze1(int &cheeseX, int &cheeseY);
	void maze2(int &cheeseX, int &cheeseY);
	void maze3(int &cheeseX, int &cheeseY);
	//maze I'm working on

	bool winner();
	bool loser();
};

void set_clips()
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
}

myGame::myGame()
{
	


}
void myGame::gameLoad()
{	
	IMG_INIT_JPG;
	IMG_INIT_PNG;
	TTF_Init( );
	font = TTF_OpenFont("lazy.ttf", 20);//right now it's that tutorials font, I need to change it
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	mouse = IMG_Load("mouseanimate.png");
	cat = IMG_Load("badcat.bmp");
	background = IMG_Load("bricks2.jpg");//I'm stealing this photo from a colleague for now black.png for black screen
	cheese = IMG_Load("cheese.jpg");
	win = IMG_Load("youwin.png");
	lose = IMG_Load("youlose.png");
	music = Mix_LoadMUS("RatRace.wav");
	loseMusic = Mix_LoadMUS("loser.wav");
	foxlogo = Mix_LoadMUS("foxlogo.wav");
	SDL_SetColorKey(mouse,SDL_SRCCOLORKEY,SDL_MapRGB(mouse->format, 255, 0, 0));//argument to color key mouse to background
	SDL_SetColorKey(cat,SDL_SRCCOLORKEY,SDL_MapRGB(cat->format, 255, 0, 0));//argument to color key mouse to background
	bump = Mix_LoadWAV("knocking.wav");//it's a bass drum manipulated
}

void myGame::musicDone()
{
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
}

void myGame::gameInit()
{
	SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO | SDL_INIT_TIMER);//initializes all subsystems
	Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	gameRunning = true;
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP, SDL_SWSURFACE);
	SDL_WM_SetCaption("Rat Race", NULL);
	//Start the timer
    start = SDL_GetTicks();

	srand(unsigned int(time(NULL)));
	int whichMaze = rand() % (NUMBEROFMAZES) + 1;
	//Set the walls
	//use to fast set some walls
	/*
	for (int i = 1; i < 14; i ++)
	{
		wall[i].x = 60 * i;
		if (i % 2 == 0 )
		{
			wall[i].y=rand() % (340) + 60;
		}
		wall[i].w = WALL_WIDTH;
		wall[i].h = WALL_HEIGHT;
		wallWidth[i] = WALL_WIDTH;
		wallHeight[i] = WALL_HEIGHT;
	}
	cheeseX = rand() % (600) + 100;
	cheeseY = rand() % (400) + 60;
	*/
	switch (whichMaze)
	{
	case 1: 
		maze1(cheeseX, cheeseY);
		break;
	case 2:
		maze2(cheeseX, cheeseY);
		break;
	case 3:
		maze3(cheeseX, cheeseY);
		break;
	}
	//maze1(cheeseX, cheeseY);
	//maze2(cheeseX, cheeseY);
	//maze3(cheeseX, cheeseY);
	
	

}

void myGame::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* &clip = NULL)
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

bool myGame::checkCollision(int i)
{
	bool mouseCollide = false;
	//wall sides
	int leftwall = wall[i].x;
	int rightwall = wall[i].x + wallWidth[i] -20;
	int topwall = wall[i].y;
	int bottomwall = wall[i].y + wallHeight[i] ;
	//mouse sides
	int leftmouse = dstX;
	int rightmouse = dstX + MOUSEWIDTH - 10;
	int topmouse = dstY;
	int bottommouse = dstY + MOUSEHEIGHT;

   //If any of the sides from A are outside of B
    
	if( rightmouse > leftwall )
    {
        mouseCollide = true;
		if ( topmouse > bottomwall)
		{
			mouseCollide = false;
		}
		if ( leftmouse > rightwall)
		{
			mouseCollide = false;
		}
		if ( bottommouse < topwall)
		{
			mouseCollide = false;
		}

	}
	else 
	{
		mouseCollide = false;
	}
	if (mouseCollide)
	{
		Mix_PlayChannel(5, bump, 0);
	}

	return mouseCollide;
}

void myGame::draw_cat (int catX, int catY, int catdX, int catdY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect src;
	src.x = catX;
	src.y = catY;
	src.w = MOUSEWIDTH;
	src.h = MOUSEHEIGHT;

	SDL_Rect dst;
	dst.x = catdX;
	dst.y = catdY;
	dst.w = MOUSEWIDTH;
	dst.h = MOUSEHEIGHT;

	SDL_BlitSurface(source,&src,destination,&dst);
}

bool myGame::checkCheeseColl(int cheeseX, int cheeseY)
{
	bool mouseCollide = false;
	//cheese sides

	int leftcheese = cheeseX;
	int rightcheese = cheeseX + CHEESEWIDTH -35;
	int topcheese = cheeseY;
	int bottomcheese = cheeseY + CHEESEHEIGHT -30;


	//mouse sides
	int leftmouse = dstX;
	int rightmouse = dstX + MOUSEWIDTH - 20;
	int topmouse = dstY;
	int bottommouse = dstY + MOUSEHEIGHT -20;

   //If any of the sides from A are outside of B
    
	if( rightmouse > leftcheese )
    {
        mouseCollide = true;
		if ( topmouse > bottomcheese)
		{
			mouseCollide = false;
		}
		if ( leftmouse > rightcheese)
		{
			mouseCollide = false;
		}
		if ( bottommouse < topcheese)
		{
			mouseCollide = false;
		}

	}
	else 
	{
		mouseCollide = false;
	}

	return mouseCollide;
}

void myGame::mouseMotion()
{
		
	
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState( NULL );
	//press m for music
	if (keystates[ SDLK_m ])
	{
		Mix_PlayMusic(music, -1);//infinite loop of playing
		keystates [SDLK_m] = false;
	}
	if (keystates[ SDLK_q ])
	{
		Mix_HaltMusic();
		keystates [SDLK_q] = false;
	}

	
	//If buttons pressed these are the mouses velocities and collision wall checks
    if( keystates[ SDLK_LEFT ] )
    {	
		
        dstX -=MOUSESPEED;
		
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_LEFT ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_LEFT] = false;
				}
				dstX +=MOUSESPEED;
			}
		}
		
    }
	if(keystates[ SDLK_UP ])
	{
		
		dstY -=MOUSESPEED;
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_UP ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_UP] = false;
				}
				dstY +=MOUSESPEED;
			}
		}

	
	}
	
	if(keystates[ SDLK_RIGHT ])
	{	
		dstX +=MOUSESPEED;
			 //Show the stick figure
		status = MOUSERIGHT;
		frame ++;
    if( status == MOUSERIGHT )
    {
        apply_surface( MOUSESPEED, SCREEN_HEIGHT - MOUSERIGHT, mouse, screen, &clipsRight[ frame ] );
    }
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_RIGHT ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_RIGHT] = false;
				}
				
				dstX -=MOUSESPEED;
			}
		}
	}
	if(keystates[ SDLK_DOWN ])
	{
		dstY +=MOUSESPEED;
		
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_DOWN ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_DOWN] = false;
				}
				dstY -=MOUSESPEED;
			}
		}

	}
	//collision screen checks
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

}

void myGame::gameInput()
{
	
	SDL_Event event;//does all this in a loop until a false
	if(SDL_PollEvent(&event))//blah deleted how to close the screen
	{
		if(event.type == SDL_QUIT)
		{
			gameRunning = false;
		}
	}
	myGame::mouseMotion();
	//cat motion
	catdX += 5;

	//collision screen checks
	if (catdX < 0)
	{
		catdX = 0;//yea set these to -catdX w/e still fun to watch it jump
	}
	if (catdY < 0)
	{
		catdY = 0;
	}
	if (catX + MOUSEWIDTH > SCREEN_WIDTH)
	{
		catdX = SCREEN_WIDTH - MOUSEWIDTH;
	}
	if (catdY + MOUSEHEIGHT > SCREEN_HEIGHT)
	{
		catdY = SCREEN_HEIGHT - MOUSEHEIGHT;
	}

	//checks if timer is gone
		//checks if mouse collides with cheese
    if (checkCheeseColl(cheeseX, cheeseY))
	{
		winner();
	}
		
	if (loseTime < 30)
	{
		loser();
	}

}

void myGame::gameDraw()
{

	//The timer's time as a string
     std::stringstream time;
	//Convert the timer's time to a string that countdowns
    time << "Till you die: " << countDown - SDL_GetTicks();
	loseTime = countDown - SDL_GetTicks();
    seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );//Render the time surface
	apply_surface(0,0,background,screen);//applies background
	apply_surface(cheeseX,cheeseY,cheese,screen);//applies cheese
    apply_surface( 460, 20, seconds, screen );//Apply timer message


	
	//sets multiple walls at once
	for (int i = 1; i < NUMBER_WALLS; i++)
	{
		SDL_FillRect( screen, &wall[i], SDL_MapRGB( screen->format, 0x255, 0x000, 0x000 ) );// black this when ready
	}
	draw_mouse(srcX,srcY,dstX,dstY,MOUSEWIDTH,MOUSEHEIGHT, mouse, screen);//applies mouse
	draw_cat(catX,catY,catdX,catdY,MOUSEWIDTH,MOUSEHEIGHT, cat, screen);//applies cat

}
void myGame::gameUpdate()
{
	
	SDL_Flip(screen);
}

bool myGame::winner()
{
	SDL_FreeSurface(background);//frees previous background from memory, if I want multiple lvls probably shouldn't do this till end
	apply_surface(0,0, win, screen);//applies win photo
	Mix_PlayMusic(foxlogo, 0);//cues fox logo
	gameRunning = false;
	return gameRunning;
}

bool myGame::loser()
{
	SDL_FreeSurface(background);//frees previous background from memory, if I want multiple lvls probably shouldn't do this till end
	apply_surface(0,0, lose, screen);//applies win photo
    Mix_PlayMusic(loseMusic, 0);//cues fox logo
	gameRunning = false;
	return gameRunning;
}

void myGame::gameCleanUp()
{
	Mix_HaltMusic();
	
	Mix_CloseAudio();
	//Free the time surface
    SDL_FreeSurface( seconds );
	music = NULL;
	SDL_Quit();
	exit(0);

}
bool myGame::runningState()
{
	return gameRunning;
}