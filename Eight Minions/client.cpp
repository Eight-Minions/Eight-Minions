#include "client.h"
#include "FPS_Regulator.h"


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

	if( TTF_Init() == -1 )
	{
		return -1;   
	}

	//Sets window caption
	SDL_WM_SetCaption( "Eight Minions", NULL );
	//create screen, params are width in pixels, height in pixels, bpp, and flags
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE);

	Cblack = makeColor(0,0,0);
	Cwhite = makeColor(255,255,255);
	Cblue = makeColor(30,70,255);
	this->loadFiles();
	this->initText();


	socketset = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketset, this->sd);
	initButtons();
	return 1;
}

void client::loadFiles()
{
	//loading files here
	this->background = IMG_Load("images/Minions_UI_ShittyGrid.png");
	font = TTF_OpenFont( "pirulen.ttf", 14 ); //create a font of the type in the file, and of size 14

	creepImages[NORM] = LoadImageCK("norm.png");
	creepImages[FAST] = LoadImageCK("fast.png");
	creepImages[SWARM] = LoadImageCK("swarm.png");
	creepImages[TANK] = LoadImageCK("tank.png");
	creepImages[TITAN] = LoadImageCK("titan.png");
	creepImages[FATTY] = LoadImageCK("fatty.png");

	towerImages[STRUCTURE] = LoadImageCK("images/structure.png");
	towerImages[NORMCREEPTOWER] = LoadImageCK("images/spawnTower.png");
	towerImages[NORMTOWER] = LoadImageCK("images/normTower.png");
	towerImages[FASTTOWER] = LoadImageCK("images/fastTower.png");

	attackImage = LoadImageCK("images/testAttack.png");

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 5; j++)
			SpriteMaps[i][j] = newRect(j * GRID_SIZE,i * GRID_SIZE,GRID_SIZE,GRID_SIZE);
	}
}

void client::cleanup()
{
	//do all freeing of memory and cleanup type stuff here

	cout << "Cleanup needs more work\n";

	SDLNet_UDP_Close(UDPsock);

	// Close our server socket, cleanup SDL_net and finish!
	SDLNet_TCP_Close(sd);

	SDLNet_Quit();
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
	int n_rec = 0;

	mouseClickMode = 0;

	FPS_Regulator *reg = new FPS_Regulator(MAX_FPS);


	while(run)
	{
		reg->start();
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
					//event.button.x; //x coordinate of click on the window
					//event.button.y; //y coordinate of click on the window

					if(buttons[0]->wasClicked(event.button.x, event.button.y))
					{
						if(mouseClickMode == DEFAULT_MODE)
							mouseClickMode = PLACE_FOUNDATION_MODE; 
						else
							mouseClickMode = DEFAULT_MODE;
					}

					if(mouseClickMode == PLACE_FOUNDATION_MODE)
					{
						if(placeTower(event.button.x,event.button.y))
						{
							mouseClickMode = DEFAULT_MODE;
							buttons[0]->setClick(false);
							coord placeC = getClickCoord(event.button.x,event.button.y);
							//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
							sendToServerUDP(UpdMess(self->getPnum(),TOWER, TOWERPLACE,placeC.x,placeC.y).getMT());
						}
					}


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


		reg->killTime();
	}

	this->cleanup();
	//dump.close();
	return 0;
}

void client::displayCreeps()
{
	cListNode<creep*> *cur = creeps.getStart();
	while(cur != NULL)
	{
		cur->getData()->displayCreep(screen,creepImages[cur->getData()->getType()], SpriteMaps[cur->getData()->getDispDir()]);
		cur = cur->getNext();
	}
}

void client::displayTowers()
{
	cListNode<structure*> *cur = towers.getStart();
	while (cur != NULL)
	{
		cur->getData()->displayTower(screen, towerImages[cur->getData()->getType()]);
		cur = cur->getNext();
	}
}

void client::displayMisc()
{
	for(int i = 0; i < attacks.size(); i++)
	{
		//CHECK IF TARGET CREEP STILL EXISTS
		if(creeps.checkForObjectWithID(attacks[i]->getTarget()))
		{
			if(attacks[i]->update(creeps.getObjectWithID(attacks[i]->getTarget())->getX(),creeps.getObjectWithID(attacks[i]->getTarget())->getY()))
			{
				attacks[i]->display(screen,attackImage);
				attackAnim *temp = attacks[i];
				attacks.erase(attacks.begin() + i);
				delete temp;
			}
			else
				attacks[i]->display(screen,attackImage);
		}
	}
}

void client::displayUI()
{
	//Blit the text objects
	for(int i = 0; i < 4; i++)
		SDL_BlitSurface(text[i], NULL,screen,textRects[i]);


	buttons[0]->display(screen);
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

	buttons[0] = new Button("images/towerButton",648,57,71,92);

}

void client::initText()
{
	char buff[8];
	textRects[0] = newRect(10,10,0,0);
	text[0] = TTF_RenderText_Solid( font, "Current Health: ", Cwhite);
	textRects[1] = newRect(200,10,0,0);
	text[1] = TTF_RenderText_Solid( font, _itoa(self->getHealth(),buff,10), Cwhite);
	textRects[2] = newRect(240,10,0,0);
	text[2] = TTF_RenderText_Solid( font, "Money:", Cblack);
	textRects[3] = newRect(325,10,0,0);
	text[3] = TTF_RenderText_Solid(font, _itoa(self->getMoney(),buff,10), Cblack);
}

bool client::placeTower( int x, int y )
{
	//find out what grid spot (if any) was clicked
	//check if a tower exists in that spot
	//if none, check if player has enough money
	//if they do, send message to server to buy the tower
	//server will then make one more check of all the requirements
	//and then place it and subtract the given amount of money
	//and then recalculate the nodemap and then the creep paths
	if(x >= BOARD_X_OFFSET && x < BOARD_X_OFFSET + (GRID_SIZE * MAPSIZE_X) &&
		y >= BOARD_Y_OFFSET && y < BOARD_Y_OFFSET + (GRID_SIZE * MAPSIZE_X))
	{
		coord temp = getClickCoord(x, y);

		if(self->getMoney() < 2)
		{
			return false;
		}
		return true;
		/*else
		{
		int t_check = 1;
		for(cListNode<structure*> *cur = towers.getStart(); cur != NULL && t_check; cur = cur->getNext())
		{
		if (cur->getData()->getX() == temp.x && cur->getData()->getY() != temp.y)
		{
		return false;
		}
		}
		coord temp_c;
		int c_check = 1;
		for(cListNode<creep*> *cur = creeps.getStart(); cur != NULL && c_check; cur = cur->getNext() )
		{
		temp_c = getClickCoord(cur->getData()->getX(),cur->getData()->getY());
		if(temp.x == temp_c.x && temp.y == temp_c.y )
		{
		return false;
		}
		}
		return true;
		}*/
	}
	else
		return false;
}





