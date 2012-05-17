#include "client.h"
#include "FPS_Regulator.h"


client::client()
{
	this->ip = new IPaddress;
	baseLevel = 1;
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
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_DOUBLEBUF | SDL_HWSURFACE); //end flag was just SDL_SWSURFACE
	this->self = new player;
	if(gameType == 1)
		self->setPnum(1);
	gMap = new gameMap(self);
	Cblack = makeColor(0,0,0);
	Cwhite = makeColor(255,255,255);
	Cblue = makeColor(30,70,255);
	this->loadFiles();
	this->initText();

	initButtons();
	return 1;
}

void client::loadFiles()
{
	//loading files here
	this->background = IMG_Load("images/minions_bg_ui.png");
	grid = IMG_Load("images/sepGrid.png");
	SDL_SetAlpha(grid,SDL_SRCALPHA,128);
	gridRect = newRect(BOARD_X_OFFSET,BOARD_Y_OFFSET,0,0);
	font = TTF_OpenFont( "pirulen.ttf", 13 ); //create a font of the type in the file, and of size 13
	font10 = TTF_OpenFont("pirulen.ttf",10 );
	string filepath;
	string temp;

	for(int i = 0; i < 2; i++)
	{
		filepath = "images/";
		filepath += ('1' + i);
		filepath += '/';

		for(int j = 0; j < NUM_CREEPS; j++)
			creepImages[i][j] = NULL;
		temp = filepath + "norm.png";
		creepImages[i][NORM] = LoadImageCK(temp);
		temp = filepath + "Minions_Creeps_Fast_Top_Sprite.png";
		creepImages[i][FAST] = LoadImageCK(temp);
		temp = filepath + "Minions_Creeps_Swarm_Top_Sprite.png";
		creepImages[i][SWARM] = LoadImageCK(temp);
		temp = filepath + "Minions_Creeps_High-A_Top_Sprite.png";
		creepImages[i][TANK] = LoadImageCK(temp);
		temp = filepath + "Minions_Creeps_Boss_Top_Sprite.png";
		creepImages[i][TITAN] = LoadImageCK(temp);
		temp = filepath + "Minions_Creeps_High-H_Top_Sprite.png";
		creepImages[i][FATTY] = LoadImageCK(temp);

		for(int j = 0; j < NUM_TOWERS; j++)
			towerImages[i][j] = NULL;

		temp = filepath + "Minions_Towers_Foundation_Top.png";
		towerImages[i][STRUCTURE] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_Spawner_Top_Sprite.png";
		towerImages[i][NORMCREEPTOWER] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_Normal_Top.png";
		towerImages[i][NORMTOWER] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_Fast_Top.png";
		towerImages[i][FASTTOWER] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_AOE_Top.png";
		towerImages[i][AOETOWER] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_Heavy_Top.png";
		towerImages[i][HEAVYTOWER] = LoadImageCK(temp);
		temp = filepath + "Minions_Towers_Mine_Top.png";
		towerImages[i][MINETOWER] = LoadImageCK(temp);
		towerImages[i][OBSTACLE] = LoadImageCK("images/rock.png");
	}
	projectileAttack = LoadImageCK("images/attackAnimSprites.png");
	aoeAttack = LoadImageCK("images/aoeAttack.png");
	selectedOverlay = LoadImageCK("images/select.png");
	SDL_SetAlpha(selectedOverlay, SDL_SRCALPHA, 128);

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < ANIM_NUM; j++)
			SpriteMaps[i][j] = newRect(j * GRID_SIZE,i * GRID_SIZE,GRID_SIZE,GRID_SIZE);
	}
}

void client::cleanup()
{
	//do all freeing of memory and cleanup type stuff here

	cout << "Cleanup needs more work\n";

	SDLNet_UDP_Close(UDPsock);

	for(int p = 0; p < 2; p++)
	{
		for(int i = 0; i < NUM_TOWERS; i++)
		{
			if(towerImages[i] != NULL)
				SDL_FreeSurface(towerImages[p][i]);
		}


		for(int i = 0; i < NUM_CREEPS; i++)
		{
			if(creepImages[i] != NULL)
				SDL_FreeSurface(creepImages[p][i]);
		}
	}

	for(int i = 0; i < TEXT_NUM; i++)
	{
		if(text[i] != NULL)
		{
			SDL_FreeSurface(text[i]);
		}
	}

	if(projectileAttack != NULL)
		SDL_FreeSurface(projectileAttack);

	delete gMap;

	for(list<attackAnim*>::iterator i = gMap->attacks.begin(); i != gMap->attacks.end(); i++)
	{
		if((*i) != NULL)
			delete (*i);
	}

	delete self; //how sad...

	// Close our server socket, cleanup SDL_net and finish!
	SDLNet_TCP_Close(sd);

	delete ip;

	SDLNet_Quit();

	SDL_FreeSurface(selectedOverlay);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
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

int client::testrun()
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

int client::run(bool single)
{
	if(single)
		return runSingle();
	else
		return runMulti();
}

int client::runSingle()
{
	gameType = 1;
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	//main run loop
	run_game = 1;
	string temp;
	int n_rec = 0;

	mouseClickMode = DEFAULT_MODE;
	menuMode = 1;

	pMess = new FadeMessage(font,10,578,MAX_FPS,1,Cwhite);

	FPS_Regulator *reg = new FPS_Regulator(MAX_FPS);
	EMenemy *enemyManager = new EMenemy(this,1);

	pMess->setMessage("Play Game!");

	while(run_game)
	{
		reg->start(); //start the fps regulator
		handleInputSingle(); //handle user input
		enemyManager->iterate();
		this->display();//display will print everything out to the screen
		reg->killTime(); //wait a certain amount of time to 
	}

	this->cleanup();
	return 0;
}

int client::runMulti()
{
	gameType = 2;
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	
	//main run loop
	run_game = 1;
	string temp;
	int n_rec = 0;

	mouseClickMode = DEFAULT_MODE;
	menuMode = 1;

	pMess = new FadeMessage(font,10,578,MAX_FPS,1,Cwhite);

	FPS_Regulator *reg = new FPS_Regulator(MAX_FPS);

	pMess->setMessage("Play Game!");

	while(run_game)
	{
		reg->start(); //start the fps regulator
		handleInput(); //handle user input
		recieveMessageToQueue(); //receive and parse server messages
		this->display();//display will print everything out to the screen
		reg->killTime(); //wait a certain amount of time to 
	}

	this->cleanup();
	return 0;
}

void client::displayCreeps()
{
	cListNode<creep*> *cur = gMap->creepList.getStart();
	cListNode<creep*> *temp;
	while(cur != NULL)
	{
		cur->getData()->displayCreep(screen,creepImages[cur->getData()->getPlayer() - 1][cur->getData()->getType()], SpriteMaps[cur->getData()->getDispDir()]);
		if(!cur->getData()->isAlive())
		{
			temp = cur->getNext();
			gMap->creepList.deleteNode(cur->getIndex());
			cur = temp;
		}
		else
			cur = cur->getNext();
	}
}

void client::displayTowers()
{
	cListNode<structure*> *cur = gMap->towerList.getStart();
	while (cur != NULL)
	{
		cur->getData()->displayTower(screen, towerImages[cur->getData()->getPlayer() - 1][cur->getData()->getType()]);
		cur = cur->getNext();
	}
}

void client::displayMisc()
{
	list<attackAnim*>::iterator tempIT;
	bool check;
	for(list<attackAnim*>::iterator i = gMap->attacks.begin(); i != gMap->attacks.end(); i++)
	{
		//CHECK IF TARGET CREEP STILL EXISTS
		if(gMap->creepList.checkForObjectWithID((*i)->getTarget()) || (*i)->getType() == AREAOFEFFECT)
		{
			switch((*i)->getType())
			{
			case AREAOFEFFECT:
				check = (*i)->update(0,0);
				(*i)->display(screen,aoeAttack);
				break;
			case ATTACKONECREEP:
				check = (*i)->update(gMap->creepList.getObjectWithID((*i)->getTarget())->getX(),gMap->creepList.getObjectWithID((*i)->getTarget())->getY());
				(*i)->display(screen,projectileAttack);
				break;
			}
			if(check)
			{	
				attackAnim *temp = (*i);
				tempIT = i;
				if(i != gMap->attacks.end())
					i++;
				gMap->attacks.erase(tempIT);
				delete temp;
				if(i == gMap->attacks.end())
					break;
			}
		}
	}

	if(mouseClickMode == SELECT_TOWER_MODE)
	{
		SDL_BlitSurface(selectedOverlay,NULL,screen, textRects[25]);
	}
}

void client::displayUI()
{
	//Blit the text objects
	SDL_BlitSurface(text[0], NULL,screen,textRects[0]);
	SDL_BlitSurface(text[1], NULL,screen,textRects[1]);
	SDL_BlitSurface(text[2], NULL,screen,textRects[2]);
	SDL_BlitSurface(text[3], NULL,screen,textRects[3]);
	SDL_BlitSurface(text[25], NULL, screen, textRects[18]);

	SDL_BlitSurface(text[15 + self->getPnum()], NULL, screen, textRects[4]);

	pMess->display(screen);

	buttons[19]->display(screen);
	buttons[20]->display(screen);

	if(menuMode == 1) //tower place mode
	{
		buttons[0]->display(screen);
		buttons[1]->display(screen);
	}
	else if(menuMode == 2) //creep add mode
	{
		buttons[21]->display(screen);
		buttons[22]->display(screen);
		buttons[23]->display(screen);
		buttons[24]->display(screen);
		buttons[25]->display(screen);
		buttons[26]->display(screen);
		SDL_BlitSurface(text[31], NULL, screen, textRects[24]);
	}

	if(mouseClickMode == SELECT_TOWER_MODE)
	{
		if(self->getPnum() == curSelectedTowerPtr->getPlayer())
		{
			buttons[3]->display(screen);
			if(curSelectedTowerPtr->getType() != STRUCTURE)
			{
				buttons[4]->display(screen);
			}
		}
		if(curSelectedTowerPtr->getType() < NORMCREEPTOWER && curSelectedTowerPtr->getType() > STRUCTURE)
		{
			for(int i = 0; i < 9; i++)
				SDL_BlitSurface(text[32 + i], NULL, screen, textRects[26 + i]);
		}
		switch(curSelectedTowerPtr->getType())
		{
		case STRUCTURE:
			SDL_BlitSurface(text[8], NULL, screen, textRects[8]);
			if(curSelectedTowerPtr->getPlayer() == self->getPnum())
			{
				if(menuMode == 1)
				{
					buttons[5]->display(screen);
					buttons[6]->display(screen);
					buttons[7]->display(screen);
					buttons[8]->display(screen);
					buttons[9]->display(screen);
					SDL_BlitSurface(text[20], NULL, screen, textRects[13]);
					SDL_BlitSurface(text[21], NULL, screen, textRects[14]);
					SDL_BlitSurface(text[22], NULL, screen, textRects[15]);
					SDL_BlitSurface(text[23], NULL, screen, textRects[16]);
					SDL_BlitSurface(text[24], NULL, screen, textRects[17]);
				}
			}
			break;
		case NORMTOWER:
			SDL_BlitSurface(text[9], NULL, screen,  textRects[8]);
			break;
		case FASTTOWER:
			SDL_BlitSurface(text[11], NULL, screen, textRects[8]);
			break;
		case AOETOWER:
			SDL_BlitSurface(text[12], NULL, screen, textRects[8]);
			break;
		case HEAVYTOWER:
			SDL_BlitSurface(text[13], NULL, screen, textRects[8]);
			break;
		case NORMCREEPTOWER:
			if(curSelectedTowerPtr->getPlayer() == self->getPnum())
			{

				buttons[13]->display(screen);
				buttons[14]->display(screen);
				buttons[15]->display(screen);
				buttons[16]->display(screen);
				buttons[17]->display(screen);
				if(text[42] != NULL)
					SDL_BlitSurface(text[42], NULL,screen,textRects[36]);

			}

		case FASTCREEPTOWER:
		case TANKCREEPTOWER:
		case SWARMCREEPTOWER:
		case TITANCREEPTOWER:
		case FATTYCREEPTOWER:
			SDL_BlitSurface(text[10], NULL, screen, textRects[8]);
			if(self->getPnum() == curSelectedTowerPtr->getPlayer())
				buttons[12]->display(screen);
			break;

		}
		SDL_BlitSurface(text[15 + curSelectedTowerPtr->getPlayer()], NULL, screen, textRects[9]); //player number
		if(curSelectedTowerPtr->getType() >= NORMCREEPTOWER && curSelectedTowerPtr->getType() <= FATTYCREEPTOWER)
			SDL_BlitSurface(towerImages[curSelectedTowerPtr->getPlayer()][NORMCREEPTOWER], curSelectedTowerPtr->animRects[0], screen, textRects[10]);
		else
			SDL_BlitSurface(towerImages[curSelectedTowerPtr->getPlayer() - 1][curSelectedTowerPtr->getType()], NULL, screen, textRects[10]); //tower image
		SDL_BlitSurface(text[18], NULL, screen, textRects[11]);
		SDL_BlitSurface(text[19], NULL, screen, textRects[12]);
	}
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

	buttons[0] = new Button("images/Minions_UI_Buttons_Foundation_",649,88,71,92);
	buttons[1] = new Button("images/mineButton",561,552,71,48);
	//sell button
	buttons[3] = new Button("images/sellButton",649,564,36,36);
	//upgrade button
	buttons[4] = new Button("images/upgradeButton",649,528,36,36);
	//change type (for structures)
	buttons[5] = new Button("images/attackTowerButton",722,88,71,92);
	buttons[6] = new Button("images/spawnTowerButton",722,276,71,92);
	buttons[7] = new Button("images/fastTowerButton",722,182,71,92);
	buttons[8] = new Button("images/AOETowerButton",649,182,71,92);
	buttons[9] = new Button("images/heavyTowerButton",649,276,71,92);
	//pause button (for creep towers)
	buttons[12] = new Button("images/pauseButton",649,465,36,36);
	//change type (for creep towers)
	//13- 18
	buttons[13] = new Button("images/addFastToTower",727,490,36,36);
	buttons[14] = new Button("images/addSwarmToTower",727,527,36,36);
	buttons[15] = new Button("images/addHighHToTower",690,490,36,36);
	buttons[16] = new Button("images/addHighAToTower",690,527,36,36);
	buttons[17] = new Button("images/addTitanToTower",690,564,36,36);

	//menu buttons
	buttons[19] = new Button("images/towerMenuButton",649,58,71,28);
	buttons[20] = new Button("images/baseMenuButton",722,58,71,28);

	buttons[21] = new Button("images/Minions_UI_Buttons_Creep_Fast_",649,88,71,92);
	buttons[22] = new Button("images/Minions_UI_Buttons_Creep_Swarm_",722,88,71,92);
	buttons[23] = new Button("images/Minions_UI_Buttons_Creep_High-H_",649,182,71,92);
	buttons[24] = new Button("images/Minions_UI_Buttons_Creep_High-A_",722,182,71,92);
	buttons[25] = new Button("images/Minions_UI_Buttons_Creep_Boss_",649,276,71,92);

	//Upgrades base creep levels
	buttons[26] = new Button("images/Minions_UI_Buttons_Upgrade_", 722,276,71,92);

}

void client::initText()
{
	for(int i = 0; i < TEXT_NUM; i++)
	{
		text[i] = NULL;
		textRects[i] = NULL;
	}
	textRects[0] = newRect(10,554,0,0);
	text[0] = TTF_RenderText_Solid( font, "Current Health: ", Cwhite);
	textRects[1] = newRect(200,554,0,0);
	text[1] = TTF_RenderText_Solid( font, itos(self->getHealth()).c_str(), Cwhite);
	textRects[2] = newRect(240,554,0,0);
	text[2] = TTF_RenderText_Solid( font, "Money:", Cblack);
	textRects[3] = newRect(325,554,0,0);
	text[3] = TTF_RenderText_Solid(font, itos(self->getMoney()).c_str(), Cblack);

	textRects[4] = newRect(600,16,0,0);

	text[4] = TTF_RenderText_Solid(font10, "Cant Upgrade", Cblack);

	//for tower display
	textRects[8] = newRect(654,412,0,0); //where to display tower name
	text[8] = TTF_RenderText_Solid(font, "Structure", Cblack);
	text[9] = TTF_RenderText_Solid(font, "Basic Tower", Cblack);
	text[10] = TTF_RenderText_Solid(font, "Spawner Tower", Cblack);
	text[11] = TTF_RenderText_Solid(font, "Fast Tower", Cblack);
	text[12] = TTF_RenderText_Solid(font, "AOE Tower", Cblack);
	text[13] = TTF_RenderText_Solid(font, "Heavy Tower", Cblack);

	textRects[9] = newRect(654,427,0,0); //where to display towers owner
	text[16] = TTF_RenderText_Solid(font, "Player One", Cblack);
	text[17] = TTF_RenderText_Solid(font, "Player Two", Cblack);

	textRects[10] = newRect(650, 384,0,0); //where to display the towers image

	textRects[11] = newRect(697,389,0,0); //where to display the level text
	text[18] = TTF_RenderText_Solid(font10, "Level:", Cblack);
	textRects[12] = newRect(755,389,0,0); //where to display the level number
	text[19] = TTF_RenderText_Solid(font10, "1", Cblack);

	textRects[13] = newRect(727,154,0,0); //standard tower cost text
	text[20] = TTF_RenderText_Solid(font, "$5", Cblack);

	textRects[14] = newRect(727,342,0,0); //spawner tower cost text
	text[21] = TTF_RenderText_Solid(font, "$20", Cblack);

	textRects[15] = newRect(727,248,0,0); //fast tower cost text
	text[22] = TTF_RenderText_Solid(font, "$7", Cblack);

	textRects[16] = newRect(654,248,0,0); //AOE tower cost text
	text[23] = TTF_RenderText_Solid(font, "$30", Cblack);

	textRects[17] = newRect(654,342,0,0); //heavy tower cost text
	text[24] = TTF_RenderText_Solid(font, "$15", Cblack);

	textRects[18] = newRect(432, 558,0,0); // Base Level
	text[25] = TTF_RenderText_Solid(font, "Level 1", Cblack);


	//Spawn tower change type costs
	string t;
	string money = "$";
	textRects[19] = newRect(727,415,0,0);
	t = money + itos(fastCreepArr[0][4] * 20);
	text[26] = TTF_RenderText_Solid(font10, t.c_str(), Cblack);
	textRects[20] = newRect(727,452,0,0);
	t = money + itos(swarmCreepArr[0][4] * 20);
	text[27] = TTF_RenderText_Solid(font10, t.c_str(), Cblack);
	textRects[21] = newRect(727,489,0,0);
	t = money + itos(fattyCreepArr[0][4] * 20);
	text[28] = TTF_RenderText_Solid(font10, t.c_str(), Cblack);
	textRects[22] = newRect(727,526,0,0);
	t = money + itos(tankCreepArr[0][4] * 20);
	text[29] = TTF_RenderText_Solid(font10, t.c_str(), Cblack);
	textRects[23] = newRect(727,563,0,0);
	t = money + itos(titanCreepArr[0][4] * 20);
	text[30] = TTF_RenderText_Solid(font10, t.c_str(), Cblack);



	//Base Upgrade Cost
	textRects[24] = newRect(726,326,0,0);
	text[31] = TTF_RenderText_Solid(font10, "$200", Cblack);

	textRects[25] = newRect(0,0,0,0); //reserved for select cursor

	//tower stats!
	textRects[26] = newRect(656,445,0,0); //towers attack damage
	text[32] = TTF_RenderText_Solid(font10, "Damage:", Cblack);
	textRects[27] = newRect(750,445,0,0);
	text[33] = TTF_RenderText_Solid(font10, "0", Cblack);
	textRects[28] = newRect(656,456,0,0); //towers armor penetration
	text[34] = TTF_RenderText_Solid(font10, "Pierce:", Cblack);
	textRects[29] = newRect(750,456,0,0);
	text[35] = TTF_RenderText_Solid(font10, "0", Cblack);
	textRects[30] = newRect(656,467,0,0); //towers speed
	text[36] = TTF_RenderText_Solid(font10, "Speed:", Cblack);
	textRects[31] = newRect(750,467,0,0);
	text[37] = TTF_RenderText_Solid(font10, "0", Cblack);
	textRects[32] = newRect(656,478,0,0); //tower range
	text[38] = TTF_RenderText_Solid(font10, "Range:", Cblack);
	textRects[33] = newRect(750,478,0,0);
	text[39] = TTF_RenderText_Solid(font10, "0", Cblack);
	textRects[34] = newRect(656,489,0,0);
	text[40] = TTF_RenderText_Solid(font10, "Killcount:", Cblack);
	textRects[35] = newRect(750,489,0,0);
	text[41] = TTF_RenderText_Solid(font10, "0", Cblack);

	textRects[36] = newRect(740,575,0,0);
	text[42] = NULL; //for creep tower upgrades.

}

bool client::boardWasClicked( int x, int y)
{
	//find out what grid spot (if any) was clicked
	//check if a tower exists in that spot
	//if none, check if player has enough money
	//if they do, send message to server to buy the tower
	//server will then make one more check of all the requirements
	//and then place it and subtract the given amount of money
	//and then recalculate the nodemap and then the creep paths
	if(x >= BOARD_X_OFFSET && x < BOARD_X_OFFSET + (GRID_SIZE * MAPSIZE_X) &&
		y >= BOARD_Y_OFFSET && y < BOARD_Y_OFFSET + (GRID_SIZE * MAPSIZE_Y))
		return true;
	else
		return false;
}

bool client::towerExistsAt( coord curSelectedTower )
{
	for(cListNode<structure*> *cur = gMap->towerList.getStart(); cur != NULL; cur = cur->getNext())
	{
		if(cur->getData()->getX() == curSelectedTower.x && cur->getData()->getY() == curSelectedTower.y)
		{
			curTowerId = cur->getIndex();
			curSelectedTowerPtr = cur->getData();
			return true;
		}
	}
	return false;
}

void client::handleInput()
{
	while( SDL_PollEvent( &event ) )
	{
		if(event.type == SDL_QUIT)
		{
			run_game = 0;
		}
		if( event.type == SDL_MOUSEMOTION )
		{
			pMess->checkMouseover(event.button.x, event.button.y);
			if(mouseClickMode == SELECT_TOWER_MODE)
			{
				if(curSelectedTowerPtr->getType() == NORMCREEPTOWER)
				{
					if(buttons[13]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[26];
					}
					else if(buttons[14]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[27];
					}
					else if(buttons[15]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[28];
					}
					else if(buttons[16]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[29];
					}
					else if(buttons[17]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[30];
					}
					else if(buttons[4]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[4];
					}
					else
					{
						text[42] = NULL;
					}
				}

			}
		}
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_SPACE)
			{
				if(mouseClickMode == DEFAULT_MODE)
				{
					mouseClickMode = PLACE_FOUNDATION_MODE;
					buttons[0]->setClick(true);
				}
			}
		}
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(mouseClickMode == SELECT_TOWER_MODE)
			{
				if(curSelectedTowerPtr->getPlayer() == self->getPnum())
					buttons[3]->wasClicked(event.button.x, event.button.y);
				if(curSelectedTowerPtr->getType() != STRUCTURE)
					buttons[4]->wasClicked(event.button.x, event.button.y);
				if(curSelectedTowerPtr->getType() == STRUCTURE)
				{
					buttons[5]->wasClicked(event.button.x, event.button.y);
					buttons[6]->wasClicked(event.button.x, event.button.y);
					buttons[7]->wasClicked(event.button.x, event.button.y);
					buttons[8]->wasClicked(event.button.x, event.button.y);
					buttons[9]->wasClicked(event.button.x, event.button.y);
				}
				if(curSelectedTowerPtr->getType() == NORMCREEPTOWER)
				{
					buttons[13]->wasClicked(event.button.x, event.button.y);
					buttons[14]->wasClicked(event.button.x, event.button.y);
					buttons[15]->wasClicked(event.button.x, event.button.y);
					buttons[16]->wasClicked(event.button.x, event.button.y);
					buttons[17]->wasClicked(event.button.x, event.button.y);
				}
			}

			if(menuMode == 2)
			{
				buttons[21]->wasClicked(event.button.x, event.button.y);
				buttons[22]->wasClicked(event.button.x, event.button.y);
				buttons[23]->wasClicked(event.button.x, event.button.y);
				buttons[24]->wasClicked(event.button.x, event.button.y);
				buttons[25]->wasClicked(event.button.x, event.button.y);
				buttons[26]->wasClicked(event.button.x, event.button.y);
			}

			if(buttons[19]->wasClickedState(event.button.x, event.button.y))
			{
				menuMode = 1;
				buttons[19]->setClick(true);
				buttons[20]->setClick(false);
				mouseClickMode = DEFAULT_MODE;
			}
			if(buttons[20]->wasClickedState(event.button.x, event.button.y))
			{
				menuMode = 2;
				buttons[20]->setClick(true);
				buttons[19]->setClick(false);
			}
		}
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				//event.button.x; //x coordinate of click on the window
				//event.button.y; //y coordinate of click on the window


				if(buttons[3]->isClicked())
				{
					buttons[3]->setClick(false);
					//sell tower
					removeTowerSend(curSelectedTowerPtr->getX(),curSelectedTowerPtr->getY());
					mouseClickMode = DEFAULT_MODE;
					curSelectedTowerPtr = NULL;
				}
				if (buttons[4]->isClicked())
				{
					buttons[4]->setClick(false);
					//upgrade the towers level
					upgradeTowerSend(curSelectedTowerPtr->getX(),curSelectedTowerPtr->getY());

				}
				if (buttons[5]->isClicked())
				{
					buttons[5]->setClick(false);
					//change structure to a basic tower
					changeTowerTypeSend(curTowerId,NORMTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[6]->isClicked())
				{
					buttons[6]->setClick(false);
					//change structure to a spawner tower
					changeTowerTypeSend(curTowerId,NORMCREEPTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[7]->isClicked())
				{
					buttons[7]->setClick(false);
					//change structure to a fast tower
					changeTowerTypeSend(curTowerId,FASTTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[8]->isClicked())
				{
					buttons[8]->setClick(false);
					//change structure to an AOE tower
					changeTowerTypeSend(curTowerId,AOETOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[9]->isClicked())
				{
					buttons[9]->setClick(false);
					//change structure to an AOE tower
					changeTowerTypeSend(curTowerId,HEAVYTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[21]->isClicked())
				{
					buttons[21]->setClick(false);
					//add fast type creep to players spawner
					addTypeToBaseSend(FAST);

				}
				if (buttons[22]->isClicked())
				{
					buttons[22]->setClick(false);
					//add swarm type creep to players spawner
					addTypeToBaseSend(SWARM);

				}
				if (buttons[23]->isClicked())
				{
					buttons[23]->setClick(false);
					//add highHealth type creep to players spawner
					addTypeToBaseSend(FATTY);
				}
				if (buttons[24]->isClicked())
				{
					buttons[24]->setClick(false);
					//add highArmor type creep to players spawner
					addTypeToBaseSend(TANK);
				}
				if (buttons[25]->isClicked())
				{
					buttons[25]->setClick(false);
					//add titan type creep to players spawner
					addTypeToBaseSend(TITAN);
				}
				if (buttons[26]->isClicked())
				{
					buttons[26]->setClick(false);
					//upgrade base spawner level
					upgradeBaseSend();
				}
				if(buttons[13]->isClicked())
				{
					buttons[13]->setClick(false);
					//change spawner to spawn fast gMap->creepList.
					if(self->getMoney() >= fastCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, FASTCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[14]->isClicked())
				{
					buttons[14]->setClick(false);
					//change spawner to spawn swarm gMap->creepList.
					if(self->getMoney() >= swarmCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, SWARMCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[15]->isClicked())
				{
					buttons[15]->setClick(false);
					//change spawner to spawn high health gMap->creepList.
					if(self->getMoney() >= fattyCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId,FATTYCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[16]->isClicked())
				{
					buttons[16]->setClick(false);
					//change spawner to spawn high armor gMap->creepList.
					if(self->getMoney() >= tankCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, TANKCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[17]->isClicked())
				{
					buttons[17]->setClick(false);
					//change spawner to spawn titan gMap->creepList.
					if(self->getMoney() >= titanCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, TITANCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(mouseClickMode == SELECT_TOWER_MODE && curSelectedTowerPtr->getType() >= NORMCREEPTOWER && curSelectedTowerPtr->getPlayer() == self->getPnum())
				{
					if(buttons[12]->wasClickedState(event.button.x, event.button.y))
					{
						buttons[12]->wasClicked(event.button.x, event.button.y);
						toggleTowerSend(curTowerId);
					}
				}
				if(menuMode == 1 && buttons[0]->wasClicked(event.button.x, event.button.y))
				{
					if(mouseClickMode != PLACE_FOUNDATION_MODE)
					{
						if(mouseClickMode == PLACE_MINE_MODE)
							buttons[1]->setClick(false);
						mouseClickMode = PLACE_FOUNDATION_MODE; 
					}
					else
						mouseClickMode = DEFAULT_MODE;
				}

				if(menuMode == 1 && buttons[1]->wasClicked(event.button.x, event.button.y))
				{
					if(mouseClickMode != PLACE_MINE_MODE)
					{
						if(mouseClickMode == PLACE_FOUNDATION_MODE)
							buttons[0]->setClick(false);
						mouseClickMode = PLACE_MINE_MODE; 
					}
					else
						mouseClickMode = DEFAULT_MODE;
				}

				if(boardWasClicked(event.button.x,event.button.y))
				{
					if(mouseClickMode == DEFAULT_MODE || mouseClickMode == SELECT_TOWER_MODE)
					{
						curSelectedTower = this->getClickCoord(event.button.x, event.button.y);
						if (towerExistsAt(curSelectedTower))
						{
							mouseClickMode = SELECT_TOWER_MODE;
							menuMode = 1;
							buttons[19]->setClick(true);
							textRects[25]->x = (curSelectedTower.x * GRID_SIZE) + BOARD_X_OFFSET;
							textRects[25]->y = (curSelectedTower.y * GRID_SIZE) + BOARD_Y_OFFSET;
							recalcTowerInfo();
							updateUpgradeCost();
							SDL_FreeSurface(text[19]);
							text[19] = TTF_RenderText_Solid(font10, itos(curSelectedTowerPtr->getLevel()).c_str(),Cblack);
							if(curSelectedTowerPtr->getType() >= NORMCREEPTOWER)
								buttons[12]->setClick(curSelectedTowerPtr->isPaused());
						}
						else
							mouseClickMode = DEFAULT_MODE;
					}
					else if(mouseClickMode == PLACE_FOUNDATION_MODE)
					{
						mouseClickMode = DEFAULT_MODE;
						buttons[0]->setClick(false);
						if(self->getMoney() >= 2)
						{
							coord placeC = getClickCoord(event.button.x,event.button.y);
							bool valid = false;
							if(self->getPnum() == 1)
								if(placeC.x < MAPSIZE_X / 2)
									valid = true;
							if(self->getPnum() == 2)
								if(placeC.x >= MAPSIZE_X / 2)
									valid = true;
							//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
							if(valid)
								sendToServerUDP(UpdMess(self->getPnum(),TOWER, TOWERPLACE,placeC.x,placeC.y).getMT());
						}
						else
							pMess->setMessage("Not Enough Money...");

					}
					else if(mouseClickMode == PLACE_MINE_MODE)
					{
						if(self->getMoney() >= mineArr[0][4])
						{
							mouseClickMode = DEFAULT_MODE;
							buttons[1]->setClick(false);
							coord placeC = getClickCoord(event.button.x,event.button.y);
							//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
							sendToServerUDP(UpdMess(self->getPnum(),TOWER, MINEPLACE,placeC.x,placeC.y).getMT());
						}
						else
							pMess->setMessage("Not Enough Money for Mine...");
					}
				}
			}
		}
	}
}

void client::recalcTowerInfo()
{
	if(curSelectedTowerPtr->getType() < NORMCREEPTOWER && curSelectedTowerPtr->getType() > STRUCTURE)
	{
		SDL_FreeSurface(text[33]);
		text[33] = TTF_RenderText_Solid(font10, itos(towerArrays[curSelectedTowerPtr->getType() - 1][curSelectedTowerPtr->getLevel() - 1][0]).c_str(), Cblack); //damage
		SDL_FreeSurface(text[35]);
		text[35] = TTF_RenderText_Solid(font10, itos(towerArrays[curSelectedTowerPtr->getType() - 1][curSelectedTowerPtr->getLevel() - 1][1]).c_str(), Cblack); //armor pen
		SDL_FreeSurface(text[37]);
		text[37] = TTF_RenderText_Solid(font10, itos(towerArrays[curSelectedTowerPtr->getType() - 1][curSelectedTowerPtr->getLevel() - 1][3]).c_str(), Cblack); //speed
		SDL_FreeSurface(text[39]);
		text[39] = TTF_RenderText_Solid(font10, itos(towerArrays[curSelectedTowerPtr->getType() - 1][curSelectedTowerPtr->getLevel() - 1][2]).c_str(), Cblack); //range
	}
}

void client::updateKillcount()
{
	SDL_FreeSurface(text[40]);
	text[40] = TTF_RenderText_Solid(font10, itos(curSelectedTowerPtr->getKillcount()).c_str() , Cblack);
}

void client::updateUpgradeCost()
{
	SDL_FreeSurface(text[4]);
	string n = "$";
	int cost = curSelectedTowerPtr->updateCost(curSelectedTowerPtr->getLevel(), curSelectedTowerPtr->getType());
	n += itos(cost);
	text[4] = TTF_RenderText_Solid(font10,n.c_str(),Cblack);
}

void client::handleInputSingle()
{
	while( SDL_PollEvent( &event ) )
	{
		if(event.type == SDL_QUIT)
		{
			run_game = 0;
		}
		if( event.type == SDL_MOUSEMOTION )
		{
			pMess->checkMouseover(event.button.x, event.button.y);
			if(mouseClickMode == SELECT_TOWER_MODE)
			{
				if(curSelectedTowerPtr->getType() == NORMCREEPTOWER)
				{
					if(buttons[13]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[26];
					}
					else if(buttons[14]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[27];
					}
					else if(buttons[15]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[28];
					}
					else if(buttons[16]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[29];
					}
					else if(buttons[17]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[30];
					}
					else if(buttons[4]->wasClickedState(event.button.x,event.button.y))
					{
						text[42] = text[4];
					}
					else
					{
						text[42] = NULL;
					}
				}

			}
		}
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_SPACE)
			{
				if(mouseClickMode == DEFAULT_MODE)
				{
					mouseClickMode = PLACE_FOUNDATION_MODE;
					buttons[0]->setClick(true);
				}
			}
		}
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(mouseClickMode == SELECT_TOWER_MODE)
			{
				if(curSelectedTowerPtr->getPlayer() == self->getPnum())
					buttons[3]->wasClicked(event.button.x, event.button.y);
				if(curSelectedTowerPtr->getType() != STRUCTURE)
					buttons[4]->wasClicked(event.button.x, event.button.y);
				if(curSelectedTowerPtr->getType() == STRUCTURE)
				{
					buttons[5]->wasClicked(event.button.x, event.button.y);
					buttons[6]->wasClicked(event.button.x, event.button.y);
					buttons[7]->wasClicked(event.button.x, event.button.y);
					buttons[8]->wasClicked(event.button.x, event.button.y);
					buttons[9]->wasClicked(event.button.x, event.button.y);
				}
				if(curSelectedTowerPtr->getType() == NORMCREEPTOWER)
				{
					buttons[13]->wasClicked(event.button.x, event.button.y);
					buttons[14]->wasClicked(event.button.x, event.button.y);
					buttons[15]->wasClicked(event.button.x, event.button.y);
					buttons[16]->wasClicked(event.button.x, event.button.y);
					buttons[17]->wasClicked(event.button.x, event.button.y);
				}
			}

			if(menuMode == 2)
			{
				buttons[21]->wasClicked(event.button.x, event.button.y);
				buttons[22]->wasClicked(event.button.x, event.button.y);
				buttons[23]->wasClicked(event.button.x, event.button.y);
				buttons[24]->wasClicked(event.button.x, event.button.y);
				buttons[25]->wasClicked(event.button.x, event.button.y);
				buttons[26]->wasClicked(event.button.x, event.button.y);
			}

			if(buttons[19]->wasClickedState(event.button.x, event.button.y))
			{
				menuMode = 1;
				buttons[19]->setClick(true);
				buttons[20]->setClick(false);
				mouseClickMode = DEFAULT_MODE;
			}
			if(buttons[20]->wasClickedState(event.button.x, event.button.y))
			{
				menuMode = 2;
				buttons[20]->setClick(true);
				buttons[19]->setClick(false);
			}
		}
		if(event.type == SDL_MOUSEBUTTONUP)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				//event.button.x; //x coordinate of click on the window
				//event.button.y; //y coordinate of click on the window


				if(buttons[3]->isClicked())
				{
					buttons[3]->setClick(false);
					//sell tower
					removeTowerSend(curSelectedTowerPtr->getX(),curSelectedTowerPtr->getY());
					mouseClickMode = DEFAULT_MODE;
					curSelectedTowerPtr = NULL;
				}
				if (buttons[4]->isClicked())
				{
					buttons[4]->setClick(false);
					//upgrade the towers level
					upgradeTowerSend(curSelectedTowerPtr->getX(),curSelectedTowerPtr->getY());

				}
				if (buttons[5]->isClicked())
				{
					buttons[5]->setClick(false);
					//change structure to a basic tower
					changeTowerTypeSend(curTowerId,NORMTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[6]->isClicked())
				{
					buttons[6]->setClick(false);
					//change structure to a spawner tower
					changeTowerTypeSend(curTowerId,NORMCREEPTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[7]->isClicked())
				{
					buttons[7]->setClick(false);
					//change structure to a fast tower
					changeTowerTypeSend(curTowerId,FASTTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[8]->isClicked())
				{
					buttons[8]->setClick(false);
					//change structure to an AOE tower
					changeTowerTypeSend(curTowerId,AOETOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[9]->isClicked())
				{
					buttons[9]->setClick(false);
					//change structure to an AOE tower
					changeTowerTypeSend(curTowerId,HEAVYTOWER);
					mouseClickMode = DEFAULT_MODE;
				}
				if (buttons[21]->isClicked())
				{
					buttons[21]->setClick(false);
					//add fast type creep to players spawner
					addTypeToBaseSend(FAST);

				}
				if (buttons[22]->isClicked())
				{
					buttons[22]->setClick(false);
					//add swarm type creep to players spawner
					addTypeToBaseSend(SWARM);

				}
				if (buttons[23]->isClicked())
				{
					buttons[23]->setClick(false);
					//add highHealth type creep to players spawner
					addTypeToBaseSend(FATTY);
				}
				if (buttons[24]->isClicked())
				{
					buttons[24]->setClick(false);
					//add highArmor type creep to players spawner
					addTypeToBaseSend(TANK);
				}
				if (buttons[25]->isClicked())
				{
					buttons[25]->setClick(false);
					//add titan type creep to players spawner
					addTypeToBaseSend(TITAN);
				}
				if (buttons[26]->isClicked())
				{
					buttons[26]->setClick(false);
					//upgrade base spawner level
					upgradeBaseSend();
				}
				if(buttons[13]->isClicked())
				{
					buttons[13]->setClick(false);
					//change spawner to spawn fast gMap->creepList.
					if(self->getMoney() >= fastCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, FASTCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[14]->isClicked())
				{
					buttons[14]->setClick(false);
					//change spawner to spawn swarm gMap->creepList.
					if(self->getMoney() >= swarmCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, SWARMCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[15]->isClicked())
				{
					buttons[15]->setClick(false);
					//change spawner to spawn high health gMap->creepList.
					if(self->getMoney() >= fattyCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId,FATTYCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[16]->isClicked())
				{
					buttons[16]->setClick(false);
					//change spawner to spawn high armor gMap->creepList.
					if(self->getMoney() >= tankCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, TANKCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(buttons[17]->isClicked())
				{
					buttons[17]->setClick(false);
					//change spawner to spawn titan gMap->creepList.
					if(self->getMoney() >= titanCreepArr[0][4] * 20)
						changeSpawnerTypeSend(curTowerId, TITANCREEPTOWER);
					else
						pMess->setMessage("Not Enough Money!");
				}
				if(mouseClickMode == SELECT_TOWER_MODE && curSelectedTowerPtr->getType() >= NORMCREEPTOWER && curSelectedTowerPtr->getPlayer() == self->getPnum())
				{
					if(buttons[12]->wasClickedState(event.button.x, event.button.y))
					{
						buttons[12]->wasClicked(event.button.x, event.button.y);
						toggleTowerSend(curTowerId);
					}
				}
				if(menuMode == 1 && buttons[0]->wasClicked(event.button.x, event.button.y))
				{
					if(mouseClickMode != PLACE_FOUNDATION_MODE)
					{
						if(mouseClickMode == PLACE_MINE_MODE)
							buttons[1]->setClick(false);
						mouseClickMode = PLACE_FOUNDATION_MODE; 
					}
					else
						mouseClickMode = DEFAULT_MODE;
				}

				if(menuMode == 1 && buttons[1]->wasClicked(event.button.x, event.button.y))
				{
					if(mouseClickMode != PLACE_MINE_MODE)
					{
						if(mouseClickMode == PLACE_FOUNDATION_MODE)
							buttons[0]->setClick(false);
						mouseClickMode = PLACE_MINE_MODE; 
					}
					else
						mouseClickMode = DEFAULT_MODE;
				}

				if(boardWasClicked(event.button.x,event.button.y))
				{
					if(mouseClickMode == DEFAULT_MODE || mouseClickMode == SELECT_TOWER_MODE)
					{
						curSelectedTower = this->getClickCoord(event.button.x, event.button.y);
						if (towerExistsAt(curSelectedTower))
						{
							mouseClickMode = SELECT_TOWER_MODE;
							menuMode = 1;
							buttons[19]->setClick(true);
							textRects[25]->x = (curSelectedTower.x * GRID_SIZE) + BOARD_X_OFFSET;
							textRects[25]->y = (curSelectedTower.y * GRID_SIZE) + BOARD_Y_OFFSET;
							recalcTowerInfo();
							updateUpgradeCost();
							SDL_FreeSurface(text[19]);
							text[19] = TTF_RenderText_Solid(font10, itos(curSelectedTowerPtr->getLevel()).c_str(),Cblack);
							if(curSelectedTowerPtr->getType() >= NORMCREEPTOWER)
								buttons[12]->setClick(curSelectedTowerPtr->isPaused());
						}
						else
							mouseClickMode = DEFAULT_MODE;
					}
					else if(mouseClickMode == PLACE_FOUNDATION_MODE)
					{
						mouseClickMode = DEFAULT_MODE;
						buttons[0]->setClick(false);
						if(self->getMoney() >= 2)
						{
							coord placeC = getClickCoord(event.button.x,event.button.y);
							bool valid = false;
							if(self->getPnum() == 1)
								if(placeC.x < MAPSIZE_X / 2)
									valid = true;
							if(self->getPnum() == 2)
								if(placeC.x >= MAPSIZE_X / 2)
									valid = true;
							//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
							if(valid)
							{
								//sendToServerUDP(UpdMess(self->getPnum(),TOWER, TOWERPLACE,placeC.x,placeC.y).getMT());
								gMap->towerList.insertInOrder(new structure(1 ,self->getPnum(), STRUCTURE ,placeC.x,placeC.y));
							}
						}
						else
							pMess->setMessage("Not Enough Money...");

					}
					else if(mouseClickMode == PLACE_MINE_MODE)
					{
						if(self->getMoney() >= mineArr[0][4])
						{
							mouseClickMode = DEFAULT_MODE;
							buttons[1]->setClick(false);
							coord placeC = getClickCoord(event.button.x,event.button.y);
							//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
							sendToServerUDP(UpdMess(self->getPnum(),TOWER, MINEPLACE,placeC.x,placeC.y).getMT());
						}
						else
							pMess->setMessage("Not Enough Money for Mine...");
					}
				}
			}
		}
	}
}


