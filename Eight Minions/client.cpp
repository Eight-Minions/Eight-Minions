#include "client.h"

client::client()
{
	this->ip = new IPaddress;
}

int client::init()
{
	//Start SDL
	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		cout << "SDL Failed to initialize...\n";
		return -1;
	}

	//Sets window caption
	SDL_WM_SetCaption( "Eight Minions", NULL );
	//create screen, params are width in pixels, height in pixels, bpp, and flags
	screen = SDL_SetVideoMode(840,550,32,SDL_SWSURFACE);
	this->background = IMG_Load("background.png");

	socketset = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketset, this->sd);
	initButtons();
	return 1;
}

void client::cleanup()
{
	//do all freeing of memory and cleanup type stuff here

	cout << "Cleanup needs more work\n";
	SDL_free(background);
	SDL_Quit();
}
void client::display()
{
	SDL_BlitSurface(background, NULL, screen, NULL); //lay down background

	this->displayTowers();//displays towers first so they are below everything else
	this->displayCreeps(); //creeps on layer above towers
	this->displayMisc(); //misc: animations, tower attacks, explosions, etc. over creeps and towers.
	this->displayUI(); //any menu objects, overlay text, buttons will be on the very top
	SDL_Flip(screen);//displays everything that has been added to the screen
}

int client::run()
{
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	//main run loop. does not work at this time, but will eventually look like this.
	int run = 1;
	while(run)
	{
		if(SDL_PollEvent( &event ))
			if(event.type == SDL_QUIT)
				run = 0;


		this->recieveMessageToQueue();
		this->parseQueue();
		this->display();

		SDL_Delay(20);
	}

	this->cleanup();
	return 0;
}

int client::testrun()
{
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	//main run loop
	int run = 1;
	UpdMess testMess;
	string temp;
	int now = 0;
	int n_rec = 0;
	while(run)
	{
		//gather input - the following series of if-statements will handle all user input
		if( SDL_PollEvent( &event ) )
		{
			if(event.type == SDL_QUIT)
			{
				run = 0;
			}
			if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					event.button.x; //x coordinate of click on the window
					event.button.y; //y coordinate of click on the window

					//////////////////////////////////////////////////////////////
					//Your goal, using this information, make the game do things
					//when you click, i.e. clicking a tower displays info about it
					//clicking the 'buy' menu (or whatever we decide to have) opens 
					//a menu of things to buy. clicking a tower to buy and clicking a 
					//spot on the map checks if the tower can go there and then puts it 
					//there, subtracts money, and any other tasks that need to be done
					//some of this will require server message which i will explain/help
					//with, but i dont want to do everything. so this is not my task
					///////////////////////////////////////////////////////////////
				}

			}
		}


		//Recieve messages to queue does a lot of work
		//first it will recieve messages (while there are messages to be recieved)
		//then it will parse those messages and make changes to the game as specified by the messages
		recieveMessageToQueue();

		//display will print everything out to the screen
		this->display();


		SDL_Delay(20); //change this to be scaled by a timer
	}

	this->cleanup();
	return 0;
}


void client::parseQueue()
{

}

void client::displayCreeps()
{
	cListNode<creep*> *cur = creeps.getStart();
	while(cur != NULL)
	{
		cur->getData()->displayCreep(screen,NULL);
		cur = cur->getNext();
	}
}

void client::displayTowers()
{
	cListNode<tower*> *cur = towers.getStart();
	while (cur != NULL){
		cur->getData()->displayTower(screen);
		cur = cur->getNext();
	}
}

void client::displayMisc()
{

}

void client::displayUI()
{

}

coord client::getClickCoord(int x, int y)
{
	/*
	Gets the grid coordinate of a mouse click
	
	*/
	x -= BOARD_X_OFFSET;
	y -= BOARD_Y_OFFSET;

	x /= GRID_SIZE;
	y /= GRID_SIZE;

	coord click = {x , y};
	return click;
}

void client::initButtons()
{
	Buttons[0] = newRect(BOARD_X_OFFSET, BOARD_Y_OFFSET, MAPSIZE_X * GRID_SIZE, MAPSIZE_Y * GRID_SIZE);

}


