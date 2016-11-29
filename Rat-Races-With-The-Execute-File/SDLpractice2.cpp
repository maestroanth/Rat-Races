#include "SDL.h"
#include "SDL_image.h"
#include "myGame.h"
#include <iostream>
#include "myMazes.h"
#include "mouseanimation.h"
#include "cat.h"
using namespace std;

//http://www.youtube.com/watch?v=LpuJZxsLtz4

//Matt's security key CF0498B96D
//the goal is to create a blank (blind) and hopefully randomized maze with a timer till you lose unless you get to the check point
//next goal side scroll the screen and make longer mazes
//maybe down the road make multiple levels
int main (int argc, char* arv[])
{
	myGame myGame;

	//Load
	myGame.gameLoad();
	//Init
	myGame.gameInit();
		//While game is running
		while (myGame.runningState() == true)
		{

			myGame.setCam();
			//Draw things to screen
		
			myGame.gameDraw();

			//Handle input
			myGame.gameInput();
			
			//Update
			
			myGame.gameUpdate();//I think update refers to if the game is still running
			if (myGame.runningState() == false)
			{
				SDL_Delay(19000);
			}
		}

	//Cleanup
	
	myGame.gameCleanUp();

	return 0;
}