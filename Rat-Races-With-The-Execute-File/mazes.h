void maze1()
{
		SDL_Rect wall[NUMBER_WALLS];
	int wallWidth[NUMBER_WALLS];
	int wallHeight[NUMBER_WALLS];
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
}