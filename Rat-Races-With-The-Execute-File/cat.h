bool myGame::checkCatColl(int catX, int catY)
{
	bool mouseCollide = false;
	//cat sides

	int leftcat = catdX - dstX;
	int rightcat = catdX + CATWIDTH -25 - dstX;
	int topcat = catdY -dstY;
	int bottomcat = catdY + CATHEIGHT -20 - dstY;


	//mouse sides
	int leftmouse = dstX;
	int rightmouse = dstX + CATWIDTH - 30;
	int topmouse = dstY;
	int bottommouse = dstY + CATHEIGHT -30;

   //If any of the sides from A are outside of B
    
	if( rightmouse > leftcat )
    {
        mouseCollide = true;
		if ( topmouse > bottomcat)
		{
			mouseCollide = false;
		}
		if ( leftmouse > rightcat)
		{
			mouseCollide = false;
		}
		if ( bottommouse < topcat)
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

Uint32 myGame::catMotion(int& whichCatDir)
{

	
	static Uint32 next_time = 0;
	Uint32 now = SDL_GetTicks();
	
	if (next_time < now)
	{
		
		next_time = now + CATSPEED;

		catDir(whichCatDir);

		for (int i = 1; i < NUMBER_WALLS; i++)
		{
			if (checkCatWallCollision(i) == true)
			{
				switch (whichCatDir)
				{
				case 1:
					catdX -= CATMOTION;
					whichCatDir = rand()%4+1;
					break;
				case 2:
					catdX += CATMOTION;
					whichCatDir = rand()%4+1;
					break;
				case 3:
					catdY -= CATMOTION;
					whichCatDir = rand()%4+1;
					break;
				case 4:
					catdY += CATMOTION;
					whichCatDir = rand()%4+1;
					break;
				}
			}
		}
		return(0);
	}
	
	return(next_time-now);
}
// make cats collide with walls so I can move them randomly

void myGame::catDir(int whichCatDir)
{
	switch (whichCatDir)
	{
	case 1:
		catdX += CATMOTION;
		break;
	case 2:
		catdX -= CATMOTION;
		break;
	case 3:
		catdY += CATMOTION;
		break;
	case 4:
		catdY -= CATMOTION;
		break;
	}
}


bool myGame::checkCatWallCollision(int i)
{
	bool catCollide = false;
	//wall sides
	int leftwall = wall[i].x;
	int rightwall = wall[i].x + wallWidth[i] -20;
	int topwall = wall[i].y;
	int bottomwall = wall[i].y + wallHeight[i] ;
	//cat sides
	int leftcat = catdX;
	int rightcat = catdX + CATWIDTH - 10;
	int topcat = catdY;
	int bottomcat = catdY + CATHEIGHT;

   //If any of the sides from A are outside of B
    
	if( rightcat > leftwall )
    {
        catCollide = true;
		if ( topcat > bottomwall)
		{
			catCollide = false;
		}
		if ( leftcat > rightwall)
		{
			catCollide = false;
		}
		if ( bottomcat < topwall)
		{
			catCollide = false;
		}

	}
	else 
	{
		catCollide = false;
	}

	return catCollide;
}
