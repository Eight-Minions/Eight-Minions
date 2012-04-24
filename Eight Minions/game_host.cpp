#include "game_host.h"

int game_host::init()
{
	//init
	//here we set the size of the tower map, and the nodemap
	//the tower map holds towers and facilitates their display to the map
	//the nodemap is a boolean map of which squares are passable, this is used in pathfinding

	Tmap.resize(MAPSIZE_X);
	Nodemap.resize(MAPSIZE_X);
	for(int i = 0; i < MAPSIZE_X;i++)
	{
		Tmap[i].resize(MAPSIZE_Y);
		Nodemap[i].resize(MAPSIZE_Y);
	}

	//set the location of each players bases, these are used as goals for the creeps pathfinding
	Bases[0].x = PLAYERONEX;
	Bases[0].y = PLAYERONEY;
	Bases[1].x = PLAYERTWOX;
	Bases[1].y = PLAYERTWOY;

	//set up spawners, these manage the generation of creeps
	p1Spawner = new Spawner(this, 1, false, Bases[0]);
	p2Spawner = new Spawner(this, 2, false, Bases[1]);

	pathTestCreep = new creep(0, 1, 1, Bases[0].x, Bases[0].y);
	pathTestCreep->p.setGoal(Bases[1]);
	pathTestCreep->p.setStart(Bases[0]);

	return 0;
}

int game_host::testrun()
{
	this->init();
	this->waitForClients();

	//runs the game itself
	return 0;
}

int game_host::run()
{
	cListNode<creep*> *cur = NULL;
	cListNode<structure*> *curTower = NULL;
	cListNode<structure*> *tempTower = NULL;
	cListNode<creep*> *temp = NULL;
	int run = 1;
	int nc = 0;
	bool deletedACreep = false;

	this->init();
	this->init_net();
	//this->waitForClients();
	this->waitForClient_test();

	loadMap("TestMap.map");
	setNodemap();	
	FPS_Regulator *reg = new FPS_Regulator(MAX_FPS);

	while(run)
	{
		reg->start();
		recieveFromClients();

		p1Spawner->iterate();
		p2Spawner->iterate();

		for(curTower = towerList.getStart(); curTower != NULL;)
		{
			curTower->getData()->iterate();
			if(curTower->getData()->getType() == MINETOWER)
			{
				if(curTower->getData()->isAlive() == false)
				{
					tempTower = curTower->getNext();
					this->removeTower(curTower->getIndex(), curTower->getData()->getPlayer());
					curTower = tempTower;
					tempTower = NULL;
				}
				else
					curTower = curTower->getNext();
			}
			else
				curTower = curTower->getNext();
		}

		for(cur = creepList.getStart(); cur != NULL;)
		{ //loop through the list
			if(cur->getData()->move()) //move each creep in the list
			{
				if(players[cur->getData()->getPlayer() % 2].takeDamage())
				{
					cout << "game over man, game over...\n";
					if(getPlayer(1)->getHealth() <= 0)  
						sendMessageToQueue(UpdMess(0, GAMEOVER, 2).getMT()); //Player 1's health is 0 so Say player 2 won;
					else if(getPlayer(2)->getHealth() <= 0) 
						sendMessageToQueue(UpdMess(0, GAMEOVER, 1).getMT()); //Player 2's health is 0 so say player 1 won.
					else
						cout << "Issue in calculation of winner" << endl;
					sendMessageToQueue(UpdMess(cur->getData()->getPlayer(), PLAYERUPDATE, getPlayer(cur->getData()->getPlayer())->getHealth(), getPlayer(cur->getData()->getPlayer())->getMoney()).getMT());
					run = 0;
				}
				cur->getData()->kill(); 
				sendMessageToQueue(UpdMess(cur->getData()->getPlayer(), PLAYERUPDATE, getPlayer(cur->getData()->getPlayer())->getHealth(), getPlayer(cur->getData()->getPlayer())->getMoney()).getMT());
			}
			else
			{
				//do any additional operations on creeps here, ie health regen, burning, poison, random splitting etc
				//sendMessageToQueue(UpdMess(cur->getData()->getPlayer(), CREEP, cur->getIndex(), cur->getData()->getX(), cur->getData()->getY(), cur->getData()->getHealth()).getMT());
				sendMessageToQueue(UpdMess(cur->getData()->getPlayer(), CREEPUPDATE, cur->getIndex(), cur->getData()->getX(), cur->getData()->getY(), cur->getData()->getHealth(), cur->getData()->getType(), cur->getData()->getLevel()).getMT());
			}
			temp = cur;
			cur = cur->getNext();
			if(temp->getData()->isAlive() == false)
			{
				sendMessageToQueue(UpdMess(temp->getData()->getPlayer(),CREEP,temp->getIndex(),0,0,0).getMT());
				creepList.deleteNode(temp->getIndex());
				deletedACreep = true;
			}
		}
		if(deletedACreep) // Send a player update.
		{
			sendMessageToQueue(UpdMess(players[0].getPnum(), PLAYERUPDATE, players[0].getHealth(), players[0].getMoney()).getMT());
			sendMessageToQueue(UpdMess(players[1].getPnum(), PLAYERUPDATE, players[1].getHealth(), players[1].getMoney()).getMT());
		}
		deletedACreep = false;
		sendMessageToQueue("SEND"); //this to ensure that all updates for this pass are sent*/
		reg->killTime();
	}
	return 0;
}

void game_host::setNodemap()
{
	for(int i = 0; i < MAPSIZE_X; i++)
		for(int j = 0; j < MAPSIZE_Y; j++)
		{
			if(Tmap[i][j] != NULL)
			{
				Nodemap[i][j] = !(Tmap[i][j])->getPassable();
			}
			else
				Nodemap[i][j] = false;
		}
}

void game_host::updatePaths(int newX, int newY)
{
	cout << "updating paths";
	bool doRecalc = false;
	int i;
	int len;
	creep *temp;
	for (cListNode<creep*> *cur = creepList.getStart(); cur != NULL; cur = cur->getNext())
	{
		cout << ".";
		temp = cur->getData();
		len = temp->p.fPath.size();
		for(i = 0; i < len && !doRecalc; i++)
		{
			if(temp->p.fPath[i].x == newX && temp->p.fPath[i].y == newY)
				doRecalc = true;
		}
		if(doRecalc)
			temp->recalcPath(Nodemap);		
	}
	cout << "done!\n";
}

void game_host::spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord){
	creep *newCreep = new creep(creepType, playerNumber, creepLevel, spawnCoord.x, spawnCoord.y);
	int nIndex;
	if(playerNumber == 1)
	{
		newCreep->p.setGoal(Bases[1]);
		newCreep->p.genPath(Nodemap, false);
		nIndex = creepList.insertInOrder(newCreep);
	}
	else
	{
		newCreep->p.setGoal(Bases[0]);
		newCreep->p.genPath(Nodemap, false);
		nIndex = creepList.insertInOrder(newCreep);
	}
	sendMessageToQueue(UpdMess(playerNumber,NEWCREEP,nIndex,newCreep->getX(),newCreep->getY(),newCreep->getHealth(),newCreep->getType(),newCreep->getLevel()).getMT());
}

void game_host::spawnCreep( creep *newCreep )
{
	creepList.insertInOrder(newCreep);
}

int game_host::placeTower(int playerNumber, int towerType, int x, int y)
{
	int newTowerID = 0;
	if(Tmap[x][y] == NULL)
	{
		if(towerType == STRUCTURE)
		{
			if(Tmap[x][y] == NULL)
			{
				if(2 <= this->getPlayer(playerNumber)->getMoney())
				{
					Nodemap[x][y] = true;
					if(!pathTestCreep->p.genPath(Nodemap, false))
					{
						Nodemap[x][y] = false;
						return 0;
					}
					structure *newStructure = new structure(STRUCTURESTARTLEVEL, playerNumber, towerType, x, y);
					this->getPlayer(playerNumber)->spendMoney(2);
					sendMessageToQueue(UpdMess(playerNumber, PLAYERUPDATE, getPlayer(playerNumber)->getHealth(), getPlayer(playerNumber)->getMoney()).getMT());
					newTowerID = this->towerList.insertInOrder(newStructure);
					Tmap[x][y] = newStructure;
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else if(towerType >= NORMTOWER && towerType <= HEAVYTOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Standard_Tower *newTower = new Standard_Tower(STANDARDTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
				{
					this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else
					return 0;
			}
			else return 0;
		}
		else if(towerType == MINETOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Mine *newTower = new Mine(MINETOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
				{
					this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else
					return 0;
			}
			else return 0;
		}
		else if(towerType == OBSTACLE)
		{
			if(Tmap[x][y] == NULL)
			{
				Obstacle *newTower = new Obstacle(OBSTACLE, x, y);
				newTowerID = this->towerList.insertInOrder(newTower);
				Tmap[x][y] = newTower;
			}
			else
				return 0;
		}
		else if(towerType >= NORMCREEPTOWER && towerType <= FATTYCREEPTOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Creep_Tower *newTower = new Creep_Tower(CREEPTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
				{
					int newCost = newTower->getCost();
					this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else 
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
		updatePaths(x,y);
		sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, newTowerID, x, y, towerType).getMT());
		sendMessageToQueue(UpdMess(playerNumber, PLAYERUPDATE, getPlayer(playerNumber)->getHealth(), getPlayer(playerNumber)->getMoney()).getMT());
		return 1;
	}
	else
		return 0;
}

bool game_host::placeTowerForced(int playerNumber, int towerType, int x, int y, int towerID)
{
	if(towerType >= NORMTOWER && towerType <= HEAVYTOWER)
	{
		Standard_Tower *newTower = new Standard_Tower(STANDARDTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
		if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
		{
			this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
			sendMessageToQueue(UpdMess(playerNumber, PLAYERUPDATE, getPlayer(playerNumber)->getHealth(), getPlayer(playerNumber)->getMoney()).getMT());
			this->towerList.insertWithID(towerID, newTower);
			Nodemap[newTower->getX()][newTower->getY()] = true;
			Tmap[x][y] = newTower;
			sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, towerID, x, y, towerType).getMT());
			return true;
		}
		else
			return false;
	}
	else if(towerType == OBSTACLE)
	{
		Obstacle *newTower = new Obstacle(OBSTACLE, x, y);
		this->towerList.insertWithID(towerID, newTower);
		Nodemap[newTower->getX()][newTower->getY()] = true;
		Tmap[x][y] = newTower;
		sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, towerID, x, y, towerType).getMT());
	}
	else if(towerType == MINETOWER)
	{
		Mine *newTower = new Mine(MINETOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
		if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
		{
			this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
			this->towerList.insertWithID(towerID, newTower);
			Nodemap[newTower->getX()][newTower->getY()] = true;
			Tmap[x][y] = newTower;
			sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, towerID, x, y, towerType).getMT());
			return true;
		}
		else
			return false;
	}
	else if(towerType >= NORMCREEPTOWER && towerType <= FATTYCREEPTOWER)
	{
		Creep_Tower *newTower = new Creep_Tower(CREEPTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
		if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
		{
			this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
			this->towerList.insertWithID(towerID, newTower);
			Nodemap[newTower->getX()][newTower->getY()] = true;
			Tmap[x][y] = newTower;
			sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, towerID, x, y, towerType).getMT());
			return true;
		}
		else 
			return false;
	}
	else
		return false;
	return false;
}
bool game_host::removeTower(int towerID, int playerNum)
{
	if(towerList.checkForObjectWithID(towerID))
	{
		//int remPlayer = towerList.getNodeWithID(towerID)->getData()->getPlayer();
		sendMessageToQueue(UpdMess(playerNum, TOWER, TOWERDELETE, towerID).getMT());  // Sends back the delete confirmation (aka a delete command for the client);
		Tmap[towerList.getNodeWithID(towerID)->getData()->getX()][towerList.getNodeWithID(towerID)->getData()->getY()] = NULL;
		Nodemap[towerList.getNodeWithID(towerID)->getData()->getX()][towerList.getNodeWithID(towerID)->getData()->getY()] = false;
		this->getPlayer(playerNum)->addMoney(towerList.getNodeWithID(towerID)->getData()->getSellReward());
		sendMessageToQueue(UpdMess(playerNum, PLAYERUPDATE, this->getPlayer(playerNum)->getHealth(), this->getPlayer(playerNum)->getMoney()).getMT());
		towerList.deleteNode(towerID);
		return true;
	}
	return false;
}
bool game_host::removeTowerLocal(int towerID)
{
	if(towerList.checkForObjectWithID(towerID))
	{
		Tmap[towerList.getNodeWithID(towerID)->getData()->getX()][towerList.getNodeWithID(towerID)->getData()->getY()] = NULL;
		Nodemap[towerList.getNodeWithID(towerID)->getData()->getX()][towerList.getNodeWithID(towerID)->getData()->getY()] = false;
		towerList.deleteNode(towerID);
		return true;
	}
	return false;
}
cList<creep*> *game_host::getCreepList()
{
	return &creepList;
}
player * game_host::getPlayer(int playerNumber)
{
	if(playerNumber == 1)
		return &players[0];
	else if(playerNumber == 2)
		return &players[1];
	else
		return NULL;
}

bool game_host::isEmptyLocation(int xLoc, int yLoc)
{
	cListNode<creep*> *curCreepNode = creepList.getStart();
	int compX, compY;
	while(curCreepNode != NULL)
	{
		compX = curCreepNode->getData()->getX();
		if((compX - BOARD_X_OFFSET > (xLoc - 1) * GRID_SIZE) && (compX - BOARD_X_OFFSET < (xLoc + 1) * GRID_SIZE))
		{
			compY = curCreepNode->getData()->getY();
			if((compY - BOARD_Y_OFFSET > (yLoc - 1) * GRID_SIZE) && (compY - BOARD_Y_OFFSET < (yLoc + 1) * GRID_SIZE))
				return false;
		}
		curCreepNode = curCreepNode->getNext();
	}
	if(Tmap[xLoc][yLoc] != NULL)
		return false;
	return true;
}
bool game_host::changeStructure(int structureID, int newType)
{
	int setX = 0;
	int setY = 0;
	int playerNumber = 0;
	int cost = 0;
	if(towerList.checkForObjectWithID(structureID))
	{
		if(towerList.getNodeWithID(structureID)->getData()->getType() == STRUCTURE)
		{
			// Set values
			setX = towerList.getNodeWithID(structureID)->getData()->getX();
			setY = towerList.getNodeWithID(structureID)->getData()->getY();
			playerNumber = towerList.getNodeWithID(structureID)->getData()->getPlayer();
			switch(newType)
			{
			case NORMTOWER:
				cost = basicArr[0][4];
				break;
			case FASTTOWER:
				cost = fastArr[0][4];
				break;
			case AOETOWER:
				cost = areaOfEffectArr[0][4];
				break;
			case HEAVYTOWER:
				cost = heavyArr[0][4];
				break;
			case NORMCREEPTOWER:
				cost = normCreepArr[0][4] * 20;
				break;
			default:
				cout << "tower type not added...";
			}
			// Remove the old tower
			if(getPlayer(playerNumber)->getMoney() >= cost)
			{
				removeTowerLocal(structureID);
				return placeTowerForced(playerNumber, newType, setX, setY, structureID);
			}
		}
	}
	return false;
}

string game_host::getMapName()
{
	return mapName;
}
bool game_host::loadMap(string filename)
{
	obstructionList.clear();
	string buff;
	ifstream input;
	input.open(filename.c_str(),ifstream::in); 
	int readArray[MAPSIZE_X][MAPSIZE_Y];
	if(input!= NULL)
	{
		int yCount = 0;
		while(!input.eof())
		{
			input >> buff;
			if(buff.length() == MAPSIZE_X)
			{
				for(int xCount =  0; xCount < buff.length(); xCount++)
				{
					if(buff[xCount] == '1')
					{
						readArray[xCount][yCount] = 1;
					}
					else if(buff[xCount] == '0')
					{
						readArray[xCount][yCount] = 0;
					}
					else
					{
						cout << "Error reading file: Unexpected character. Not 1 or 0" << endl;
					}
				}
			}
			else
			{
				cout << "Error reading file: Invalid X line length" << endl;
				return false;
			}
			yCount++;
		}
		if(yCount != MAPSIZE_Y)
		{
			cout << "Error reading file: Invalid Y line length" << endl;
			return false;
		}
	}
	else
	{
		cout << "File not found, unable to load" << endl;	
		return false;
	}
	for(int xLoc = 0; xLoc < MAPSIZE_X; xLoc++)
	{
		for(int yLoc = 0; yLoc < MAPSIZE_Y; yLoc++)
		{
			if(readArray[xLoc][yLoc] == 1)
			{
				obstructionList.push_back(gC(xLoc,yLoc));
			}
		}
	}
	for(int i = 0; i < obstructionList.size(); i++)
	{
		placeTower(1, OBSTACLE, obstructionList.at(i).x, obstructionList.at(i).y);
	}
	input.close();
	return true;
}