//intergers by GOD

const int SCREEN_WIDTH = 880;
const int SCREEN_HEIGHT = 400;
const int SCREEN_BPP = 32;
const int WALL_WIDTH = 5;//for verticals
const int WALL_HEIGHT = 340;
const int NUMBER_WALLS = 30;//hopefully more walls than i ever need
const int WALL_HEIGHT2 = 5;//for horizontals
const int WALL_WIDTH2 = 570;
const int NUMBEROFMAZES = 3;
const int NUMOFMOUSECLIPS = 4;
const int LEVELWIDTH = 1200;
const int LEVELHEIGHT = 800;
const int FIXLEVELPIXH = 320;
const int FIXLEVELPIXV = 400;
//Its current frame
int mouseframe = 0;
//The camera
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//Its animation status
int mousestatus;

//The wall(s)
//animation pixels 381x 61

SDL_Rect clipsRight[ NUMOFMOUSECLIPS ];
SDL_Rect clipsLeft[ NUMOFMOUSECLIPS ];
SDL_Rect clipsUp[ NUMOFMOUSECLIPS ];
SDL_Rect clipsDown[ NUMOFMOUSECLIPS ];
SDL_Rect wall[NUMBER_WALLS];
int wallWidth[NUMBER_WALLS];
int wallHeight[NUMBER_WALLS];

int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
int audio_channels = 2;
int audio_buffers = 4096;
//SDL_Event event;
	
int const MOUSEWIDTH = 63;//size of my mouse pic
int const MOUSEHEIGHT = 30;
int const MOUSESPEED = 15;
const int MOUSERIGHT = 0;
const int MOUSELEFT = 1;
const int MOUSEMOVE = 10;//how fast animation shows

//cat motions
const int CATSPEED = 50;//speed for cat timer
const int CATMOTION = 8;//Number of pixels cat moves

const int CHEESEWIDTH = 63;
const int CHEESEHEIGHT = 30;

//black hue is 160



//mouse motion and mousebounce is back in head
int srcX = 0;
int srcY = 0;

int dstX = 0;//these you get change this is mouses position on screen
int dstY= 0;
//cat motion
int catX = 0;
int catY = 0;
const int CATDIR = 4;//how many ways the cat can turn
const int RANDOMMOVE = 5000; //in ms how fast the cat switches changes directions
//^if you want the cat to change only on collisions set it for a really long time.
int catdX = 350;
int catdY = 220;

int whichCatDir = rand() % CATDIR + 1;

const int CATWIDTH = 90;
const int CATHEIGHT = 60;
Uint32 start = NULL;
SDL_Color textColor = { 0xF0, 0xFF, 0xF0 };//text color for timer to white
const int TIMERWIDTH = 40;
int countDown = 999000;//set this variable each maze
int loseTime = 0;

	class CheeseNode
	{
	public:
		int cheeseX;
		int cheeseY;
		int cheeseSwitch;
		CheeseNode *link;
	};


typedef CheeseNode* Ptr ;

Ptr head = new CheeseNode;
	