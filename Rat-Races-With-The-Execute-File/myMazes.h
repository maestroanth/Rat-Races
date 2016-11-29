//NOTE: NEED TO SET wallWIDTH[] and wallHEIGHT[] like I do b/c that's 
//what bools the collisions!!!!!



void myGame::maze1(int &cheeseX, int &cheeseY)
{
	//manually making maze one
	wallWidth[1] = 5;//holding variable to pass
	wallHeight[1] = WALL_HEIGHT;//holding variable to pass
	wall[1].y = 0;
	wall[1].x = 60;
	wall[1].w = wallWidth[1];
	wall[1].h =	wallHeight[1];

	for (int i = 2; i < 4; i ++)
	{
		wallWidth[i] = WALL_WIDTH2;
		wallHeight[i] = WALL_HEIGHT2;
		if (i == 3)
		{
			wall[i].y = 280;
		}
		else
		{
			wall[i].y = 340;
		}
		wall[i].x = 120;
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 4; i < 6; i ++)
	{
		wallWidth[i] = 200;
		wallHeight[i] = WALL_HEIGHT2;
		wall[i].y = 220;
		if (i == 4)
		{
			wall[i].x = 120;
		}
		else
		{
			wall[i].x = 405;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 6; i < 8; i ++)
	{
		wallWidth[i] = 5;
		wallHeight[i] = 160;
		wall[i].y = 60;
		if (i == 6)
		{
			wall[i].x = 120;
		}
		else
		{
			wall[i].x = 600;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 8; i < 10; i ++)
	{
		wallWidth[i] = 120;
		wallHeight[i] = 5;
		wall[i].y = 160;
		if (i == 8)
		{
			wall[i].x = 200;
		}
		else
		{
			wall[i].x = 405;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 10; i < 12; i ++)
	{
		wallWidth[i] = 5;
		wallHeight[i] = 65;
		wall[i].y = 160;
		if (i == 10)
		{
			wall[i].x = 320;
		}
		else
		{
			wall[i].x = 400;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 12; i < 14; i++)
	{
		wallWidth[i] = 405;
		wallHeight[i] = 5;
		if (i == 12)
		{
			wall[i].y = 60;
		}
		else
		{
			wall[i].y = 110;
		}
		wall[i].x = 200;
		wall[i].w = wallWidth[i];
		wall[i].h = wallHeight[i];
	}
	
	cheeseX = 400;
	cheeseY = 170;
	

}

void myGame::maze2(int &cheeseX, int &cheeseY)
{
	for (int i = 1; i < 3; i ++)
	{
		wallWidth[i] = 200 - dstX;
		if (wallWidth[i] <= 0)
		{
			wallWidth[i] = 0;
		}
		wallHeight[i] = WALL_HEIGHT2;
		if (i % 2 == 0)
		{
			wall[i].y = 100 - dstY;
		}
		else
		{
			wall[i].y = 290 - dstY;
		}
		wall[i].x = 0;
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	for (int i = 3; i<5; i++)
	{
		wallWidth[i] = 240;
		wallHeight[i] = WALL_HEIGHT2;
		if (i % 2 == 0)
		{
			wall[i].y = 100 - dstY;
		}
		else
		{
			wall[i].y = 290 - dstY;
		}
		wall[i].x = 790 - dstX;
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

	/*
	wallWidth[5] = WALL_WIDTH;
	wallHeight[5] = 500;
	wall[5].y = 0 - dstY;
	wall[5].x = 640 - dstX;
	wall[5].w = wallWidth[5];
	wall[5].h =	wallHeight[5];
	*/
	/*
	wallWidth[6] = 460;
	wallHeight[6] = WALL_HEIGHT2;
	wall[6].y = 200 - dstY;
	wall[6].x = 133 - dstX;
	wall[6].w = wallWidth[6];
	wall[6].h =	wallHeight[6];
	*/

	//growing down wall
	wallWidth[8] = WALL_WIDTH +5;
	wallHeight[8] = MOUSEHEIGHT + dstY;
	wall[8].x = 340 - dstX;
	if (dstX >= wall[8].x)
	{
		wallWidth[8] = wallWidth[8] + dstX - 110;
	}
	if (dstY > 300)
	{
		wallHeight[8] = dstY - 40;
	}
	wall[8].y = 0;
	if (dstX > 200)
	{
		wallWidth[8] = dstY - 5;
		if( wallWidth[8] < 0)
		{
			wallWidth[8] = WALL_WIDTH +5;
		}
	}
	else
	{
		wall[8].x = 340 - dstX;
	}
	wall[8].w = wallWidth[8];
	wall[8].h =	wallHeight[8];

	wallWidth[9] = WALL_WIDTH;
	wallHeight[9] = 400;
	wall[9].y = 500 - dstY;
	wall[9].x = 260 - dstX;
	wall[9].w = wallWidth[9];
	wall[9].h =	wallHeight[9];

	wallWidth[10] = WALL_WIDTH +5;
	wallHeight[10] = LEVELHEIGHT - FIXLEVELPIXV;
	wall[10].y = dstY - 35;
	wall[10].x = 700 - dstX;
	wall[10].w = wallWidth[10];
	wall[10].h = wallHeight[10] - dstY + 35;

	//growing to the left
	wallWidth[11] = 0;
	wallHeight[11] = WALL_WIDTH;
	wall[11].x = 0 - dstX;
	if (dstY > 40)
	{
		wallWidth[11] = LEVELWIDTH; //- 110;
	}
	
	wall[11].y = 172 - dstY;
	wall[11].w = wallWidth[11];
	wall[11].h = wallHeight[11];

	//from left appears at bottom
	wallWidth[12] = 0;
	wallHeight[12] = WALL_WIDTH;
	wall[12].x = 0 - dstX;
	std::stringstream message1;
	message1 << "Press down to bounce up the box until all the way to the top";
	messageR = TTF_RenderText_Solid( font, message1.str().c_str(), textColor );
	std::stringstream message2; 
	message2 << "Press left to bounce out of the box";
	std::stringstream message3;
	message3 << "Uh oh! My mistake you might be stuck here for the rest of the time";
	if (dstY > 280)
	{
		
		wallWidth[12] = 280 + MOUSEWIDTH; //- 110;
	}
	
	if (dstX > 160 && dstX < 500 && dstY >90)
	{
		messageR = TTF_RenderText_Solid( font, message1.str().c_str(), textColor );
		apply_surface_three( 180, 350, messageR, screen);
		
		
	}

	if (dstX > 160 && dstY <90 && dstX <180)
	{
		messageR = TTF_RenderText_Solid( font, message2.str().c_str(), textColor );
		apply_surface_three( 180, 350, messageR, screen);
		
		
	}

	if(dstY < 200 && dstX>180)
	{
		messageR = TTF_RenderText_Solid( font, message3.str().c_str(), textColor );
		apply_surface_three( 180, 350, messageR, screen);
	}
	
	wall[12].y = 640 - dstY;
	wall[12].w = wallWidth[12];
	wall[12].h = wallHeight[12];

	//cheeseblock wall
	/*
	wall[11].y = 2000;
	wall[11].x = 1800;
	wall[11].w = CHEESEWIDTH +30;
	wall[11].h = CHEESEHEIGHT+30;
	*/
	


	head->cheeseX = 1300 - dstX;
	head->cheeseY = 40 - dstY;
	head->cheeseSwitch = 1;
	head->link = NULL;
	//apply_surface_three(head->cheeseX,head->cheeseY,cheese,screen);//applies cheese

	/*
	if(dstX > 600 && dstY < 50 && head->)
	{
		//wall[11].x = 1300 - dstX;
		//wall[11].y = 40 - dstY;
		head->link = new CheeseNode;
		Ptr temp = head;
		head = head->link;
		head->cheeseX = 1200 - dstX;
		head->cheeseY = 350 - dstY;
		head->link = NULL;
		delete temp;
	}
	*/
	
}


void myGame::maze3(int &cheeseX, int &cheeseY)
{
	for (int i = 1; i < 4; i++)
	{
		wallWidth[i] = 250;
		wallHeight[i] = WALL_HEIGHT2;
		wall[i].x=0;
		if (i == 1)
		{
			wall[i].y = 160;
		}
		if ( i == 2)
		{
			wall[i].y = 240;
			wall[i].x = 90;
		}
		if (i == 3)
		{
			wall[i].y = 320;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}

		wallWidth[4] = WALL_WIDTH;
		wallHeight[4] = 260;
		wall[4].x=340;
		wall[4].y=80;
		wall[4].w = wallWidth[4];
		wall[4].h =	wallHeight[4];

		wallWidth[5] = 560;
		wallHeight[5] = WALL_HEIGHT2;
		wall[5].x=0;
		wall[5].y=80;
		wall[5].w = wallWidth[5];
		wall[5].h =	wallHeight[5];

		for (int i = 6; i < 9; i++)
	{
		wallWidth[i] = 250;
		wallHeight[i] = WALL_HEIGHT2;
		if (i == 6)
		{
			wall[i].y = 160;
			wall[i].x = 430;
		}
		if ( i == 7)
		{
			wall[i].y = 240;
			wall[i].x = 340;
		}
		if (i == 8)
		{
			wall[i].y = 320;
			wall[i].x = 430;
		}
		wall[i].w = wallWidth[i];
		wall[i].h =	wallHeight[i];
	}
	cheeseX = 0;//try setting a global to maze function
	cheeseY = 95;
}	
