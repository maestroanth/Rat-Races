//Anthony Walter
//http://lazyfoo.net/SDL_tutorials/index.php

#include "SDL.h"
#include "SDL_image.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The event structure that will be used
SDL_Event event;

	//The surfaces
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *image = NULL;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );//blitting function

SDL_Surface *load_image( std::string filename ) 
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );
	 //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
		//If the image was optimized just fine
        if( optimizedImage != NULL )//this is for tutorial 5 blitting with transparancy which I haven't practiced yet
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
	    //Return the optimized image
    return optimizedImage;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Event test", NULL );
    
    //If everything initialized fine
    return true;
}



bool load_files()
{
    //Load the image
    image = load_image( "batman.bmp" );
	image = load_image("ohyea.bmp");
    
    //If there was an error in loading the image
    if( image == NULL )
    {
        return false;    
    }
    
    //If everything loaded fine
    return true;    
}


void clean_up()
{
    //Free the image
    SDL_FreeSurface( image );
    
    //Quit SDL
    SDL_Quit();    
}

int main( int argc, char* args[] )
{
	//Make sure the program waits for a quit
    bool quit = false;
	//Initialize
    if( init() == false )
    {
        return 1;    
    }
    
    //Load the files
    if( load_files() == false )
    {
        return 1;    
    }

	
	//Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;    
    }

    //Set up screen
   screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

   //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 1;    
    }

	//Set the window caption
    SDL_WM_SetCaption( "Hello World", NULL );

    //Load image
    message = load_image( "ohyea.bmp" );
    background = load_image( "batman.bmp" );

	 //Apply image to screen
	apply_surface( 0, 0, background, screen );
	apply_surface( 320, 0, background, screen );
    apply_surface( 0, 240, background, screen );
    apply_surface( 320, 240, background, screen );
	//Apply the message to the screen
    apply_surface( 180, 140, message, screen );

    //Update Screen
    SDL_Flip( screen );
	 if( SDL_Flip( screen ) == -1 )
    {
        return 1;    
    }
	//While the user hasn't quit
    while( quit == false )
    {
		 //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
			  //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }    
        }
    }
//Free the surface and quit SDL
    clean_up();

    return 0;
 
}



//blitting function
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

	    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}