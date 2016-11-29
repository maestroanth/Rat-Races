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
	SDL_Surface *messageR;//rendering messages
	SDL_Surface *message1R;
	SDL_Surface *message2R;
	SDL_Surface *message3R;
	bool gameRunning;
	//cheese coordinates
	int cheeseX;
	int cheeseY;
	
	

public:
	
	myGame();
	void gameLoad();
	void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *camera);
	void apply_surface_two(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* mouseClips, SDL_Rect *camera);
	void apply_surface_three(int x, int y, SDL_Surface *source, SDL_Surface *destination);
	void draw_mouse (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *camera);
	void draw_cat (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *camera);
	bool checkCollision(int i);
	void mouseMotion();
	Uint32 AnimationTimer();
	void gameInit();
	void gameInput();
	void gameDraw();
	void gameDraw2();
	void gameUpdate();
	void gameCleanUp();
	bool runningState();
	void musicDone();
	void mouseShow();
	void setMouseClips();
	void setCam();
	bool checkCheeseColl(int cheeseX, int cheeseY);
	bool checkCatColl(int catX, int catY);
	bool checkCatWallCollision(int i);
	void catDir(int whichCatDir);
	Uint32 catMotion(int& whichCatDir);
	//my mazes that work
	void maze1(int &cheeseX, int &cheeseY);
	void maze2(int &cheeseX, int &cheeseY);
	void maze3(int &cheeseX, int &cheeseY);
	//maze I'm working on

	bool winner();
	bool loser();
};


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
    
	mouse = IMG_Load("mouse6.png");
	
	cat = IMG_Load("catpic.bmp");
	background = IMG_Load("bg.png");//I'm stealing this photo from a colleague for now black.png for black screen
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
	SDL_WM_SetCaption("Mouse Trap! Don't get Stuck!!", NULL);// flash the avoid in a screen


	//Start the timer
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
	//maze2(cheeseX, cheeseY);
	
	/*switch (whichMaze)
	{
	case 1: 
		maze1(cheeseX, cheeseY);
		
		break;

	case 2:
		
		break;
	case 3:
		maze3(cheeseX, cheeseY);
		break;
	}
	//maze1(cheeseX, cheeseY);
	//maze2(cheeseX, cheeseY);
	//maze3(cheeseX, cheeseY);
	*/
	//maze2(head->cheeseX, head->cheeseY);
	//maze1(cheeseX, cheeseY);

}

void myGame::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* camera = NULL)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;


	SDL_BlitSurface(source,camera,destination,&rect);

}

void myGame::apply_surface_two(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* mouseClips = NULL, SDL_Rect* camera = NULL)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
  

	SDL_BlitSurface(source,mouseClips,destination,&rect);

}

void myGame::apply_surface_three(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;


	SDL_BlitSurface(source,NULL,destination,&rect);

}

void myGame::draw_mouse (int srcX, int srcY, int dstX, int dstY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *camera = NULL)
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
	int rightwall = wall[i].x + wallWidth[i];
	int topwall = wall[i].y;
	int bottomwall = wall[i].y + wallHeight[i] ;
	//mouse sides
	int leftmouse = dstX - 10;
	int rightmouse = dstX + MOUSEWIDTH -10;
	int topmouse = dstY -10;
	int bottommouse = dstY + MOUSEHEIGHT - 10;

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

void myGame::draw_cat (int catX, int catY, int catdX, int catdY, int MOUSEWIDTH, int MOUSEHEIGHT, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *camera = NULL)
{
	SDL_Rect src;
	src.x = catX;
	src.y = catY;
	src.w = CATWIDTH;
	src.h = CATHEIGHT;

	SDL_Rect dst;
	dst.x = catdX;
	dst.y = catdY;
	dst.w = CATWIDTH;
	dst.h = CATHEIGHT;

	SDL_BlitSurface(source,&src,destination,&dst);
}

bool myGame::checkCheeseColl(int cheeseX, int cheeseY)
{
	bool mouseCollide = false;
	//cheese sides

	int leftcheese = cheeseX;
	int rightcheese = cheeseX + CHEESEWIDTH -15;
	int topcheese = cheeseY;
	int bottomcheese = cheeseY + CHEESEHEIGHT -10;


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
		//SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );//blacks out screen w/e you move

		gameDraw2();
		apply_surface_two(  dstX, dstY, mouse, screen, &clipsLeft[ mouseframe ], &camera );//I need to clear the previous image
		//apply_surface( catdX, catdY, cat, screen,  &camera );
		//apply_surface( 460 + camera.x, 20 + camera.y , seconds, screen , &camera);//Apply timer message
		AnimationTimer();
		
		dstX -=MOUSESPEED;
		//loops animation
		if (mouseframe >= NUMOFMOUSECLIPS)
		{
			mouseframe = 0;
		}
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_LEFT ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_LEFT] = false;
				}
				dstX +=MOUSESPEED + 35;
			}
		}
		
    }
	
	
	if(keystates[ SDLK_UP ])
	{
		//SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		gameDraw2();
		
		dstY -=MOUSESPEED;
		apply_surface_two( dstX, dstY, mouse, screen, &clipsUp[ mouseframe ], &camera );//I need to clear the previous image
		//apply_surface( catdX, catdY, cat, screen,  &camera );
		//apply_surface( 460 + camera.x, 20 + camera.y , seconds, screen , &camera);//Apply timer message
		AnimationTimer();
		//loops animation
		if (mouseframe >= NUMOFMOUSECLIPS)
		{
			mouseframe = 0;
		}
	
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_UP ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_UP] = false;
				}
				dstY +=MOUSESPEED+MOUSEHEIGHT;
			}
		}
		
	
	}
	
	if(keystates[ SDLK_RIGHT ])
	{	
		dstX +=MOUSESPEED;
		//SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		gameDraw2();


        apply_surface_two( dstX, dstY, mouse, screen, &clipsRight[ mouseframe ], &camera );//I need to clear the previous image
		//apply_surface( catdX, catdY, cat, screen,  &camera );
		//apply_surface( 460 + camera.x, 20 + camera.y , seconds, screen , &camera);//Apply timer message
		AnimationTimer();
		//loops animation
		if (mouseframe >= NUMOFMOUSECLIPS)
		{
			mouseframe = 0;
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
				
				dstX -=MOUSESPEED + MOUSEWIDTH;
			}
		}
	}
	if(keystates[ SDLK_DOWN ])
	{
		//SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		gameDraw2();
		dstY +=MOUSESPEED;
		apply_surface_two( dstX, dstY, mouse, screen, &clipsDown[ mouseframe ], &camera );//I need to clear the previous image
		//apply_surface( catdX, catdY, cat, screen,  &camera );
		//apply_surface( 460 + camera.x, 20 + camera.y , seconds, screen , &camera);//Apply timer message
		AnimationTimer();
		//loops animation
		if (mouseframe >= NUMOFMOUSECLIPS)
		{
			mouseframe = 0;
		}
		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCollision(i) == true)
			{
				if (keystates[ SDLK_DOWN ])
				{
					Mix_PlayChannel(5, bump, 0);
					keystates [SDLK_DOWN] = false;
				}
				dstY -=MOUSESPEED +MOUSEHEIGHT;
			}
		}

	}
	
	if (dstX < 0)
	{
		dstX = 0;
	}
	if (dstY < 0)
	{
		dstY = 0;
	}
	if (dstX + MOUSEWIDTH > LEVELWIDTH - FIXLEVELPIXH)
	{
		dstX = LEVELWIDTH - MOUSEWIDTH - FIXLEVELPIXH;
	}
	if (dstY + MOUSEHEIGHT > LEVELHEIGHT - FIXLEVELPIXV)
	{
		dstY = LEVELHEIGHT - MOUSEHEIGHT - FIXLEVELPIXV;
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


	mouseMotion();
	//working on random cat motions
	static Uint32 next_time = 0;
	Uint32 now = SDL_GetTicks();

	if (next_time < now)
	{
		next_time = now + RANDOMMOVE;
		whichCatDir = rand()%4+1;
	}
	/*
	catMotion(whichCatDir);

	//collision screen checks
	if (catdX < 0)
	{
		catdX = 0;//yea set these to -catdX w/e still fun to watch it jump
		whichCatDir = rand()%4+1;
	}
	if (catdY < 0)
	{
		catdY = 0;
		whichCatDir = rand()%4+1;
	}
	if (catdX + CATWIDTH > LEVELWIDTH - FIXLEVELPIXH)
	{
		catdX = LEVELWIDTH - CATWIDTH - FIXLEVELPIXH;
		whichCatDir = rand()%4+1;
	}
	if (catdY + CATHEIGHT > LEVELHEIGHT - FIXLEVELPIXV)
	{
		catdY = LEVELHEIGHT - CATHEIGHT - FIXLEVELPIXV;
		whichCatDir = rand()%4+1;
	}
	*/
	
		//checks if mouse collides with cheese
    if (checkCheeseColl(head->cheeseX, head->cheeseY))
	{
		winner();
	}
		//checks if timer is gone
	if (loseTime < 30)
	{
		loser();
	}
	//checks if mouse collides with cat
	/*
	if (checkCatColl(catX, catY))
	{
		loser();
	}
	*/
}


void myGame::gameDraw()
{

	//The timer's time as a string
     std::stringstream time;
	//Convert the timer's time to a string that countdowns
    time << "Till you die: " << countDown - SDL_GetTicks();
	loseTime = countDown - SDL_GetTicks();
    seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );//Render the time surface
	apply_surface(0,0,background,screen, &camera);//applies background
	apply_surface_three(head->cheeseX,head->cheeseY,cheese,screen);//applies cheese
    apply_surface_three( 660, 20 , seconds, screen);//Apply timer message

	maze2( head->cheeseX, head->cheeseY);

	//sets multiple walls at once

	for (int i = 0; i < NUMBER_WALLS; i++)
	{
		SDL_FillRect( screen, &wall[i], SDL_MapRGB( screen->format, 0x255, 0x000, 0x000 ) );// black this when ready
	}
	setMouseClips();
    draw_mouse(srcX,srcY,dstX,dstY,MOUSEWIDTH,MOUSEHEIGHT, mouse, screen, &camera);//applies mouse
	//draw_cat(catX,catY,catdX-dstX,catdY-dstY,CATWIDTH,CATHEIGHT, cat, screen, &camera);//applies cat
}

void myGame::gameDraw2()//second layer for animation
{

	//The timer's time as a string
     std::stringstream time;
	//Convert the timer's time to a string that countdowns
    time << "Till you die: " << countDown - SDL_GetTicks();
	loseTime = countDown - SDL_GetTicks();
    seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );//Render the time surface
	apply_surface(0,0,background,screen, &camera);//applies background
	apply_surface_three(head->cheeseX,head->cheeseY,cheese,screen);//applies cheese
    apply_surface_three( 660 , 20, seconds, screen );//Apply timer message

	maze2( head->cheeseX, head->cheeseY);

	//sets multiple walls at once
	
	for (int i = 0; i < NUMBER_WALLS; i++)
	{
		SDL_FillRect( screen, &wall[i], SDL_MapRGB( screen->format, 0x255, 0x000, 0x000 ) );// black this when ready
	}
	setMouseClips();
    //draw_mouse(srcX,srcY,dstX,dstY,MOUSEWIDTH,MOUSEHEIGHT, mouse, screen);//applies mouse
	//draw_cat(catX,catY,catdX-dstX,catdY-dstY,CATWIDTH,CATHEIGHT, cat, screen, &camera);//applies cat
}
void myGame::gameUpdate()
{
	
	SDL_Flip(screen);
}

bool myGame::winner()
{
	SDL_FreeSurface(background);//frees previous background from memory, if I want multiple lvls probably shouldn't do this till end
	apply_surface_three(0,0, win, screen);//applies win photo
	Mix_PlayMusic(foxlogo, 0);//cues fox logo
	gameRunning = false;
	return gameRunning;
}

bool myGame::loser()
{
	SDL_FreeSurface(background);//frees previous background from memory, if I want multiple lvls probably shouldn't do this till end
	apply_surface_three(0 ,0, lose, screen);//applies win photo
    Mix_PlayMusic(loseMusic, 0);//cues fox logo
	gameRunning = false;
	return gameRunning;
}
void myGame::setCam()
{

    //Center the camera over the mouse
    camera.x = ( dstX);// - SCREEN_WIDTH / 2;
    camera.y = ( dstY);// - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVELWIDTH - SCREEN_WIDTH)
    {
        camera.x = LEVELWIDTH - SCREEN_WIDTH;
    }
    if( camera.y > LEVELHEIGHT - SCREEN_HEIGHT )
    {
        camera.y = LEVELHEIGHT - SCREEN_HEIGHT;
    }
}


void myGame::gameCleanUp()
{
	Mix_HaltMusic();
	
	Mix_CloseAudio();
	//Free the time surface
    SDL_FreeSurface( seconds );
	SDL_FreeSurface( background);
	music = NULL;
	SDL_Quit();
	exit(0);

}
bool myGame::runningState()
{
	return gameRunning;
}