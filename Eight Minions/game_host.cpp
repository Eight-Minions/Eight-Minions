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

	p1Spawner->addCreepType(SWARM);
	p2Spawner->addCreepType(FATTY);
	return 0;
}

int game_host::run()
{
	this->init();
	this->waitForClients();
	//this->sendToClients("testing!!!");
	while(1)
	{
		SDL_Delay(30);
	}
	//runs the game itself
	return 0;
}

int game_host::testrun()
{
	this->init();
	this->init_net();
	//this->waitForClients();
	this->waitForClient_test();

	// placeTower(int playerNumber, int towerType, int x, int y);

	placeTower(1,1,4,9);
	placeTower(1,1,11,11);
	placeTower(1,1,3,9);
	placeTower(1,1,12,10);
	placeTower(2,1,13,10);
	placeTower(2,1,15,8);
	placeTower(2,1,16,7);
	placeTower(2,1,16,6);
	placeTower(2,1,14,9);
	placeTower(2,1,5,10);
	placeTower(1,NORMCREEPTOWER, 3, 8);
	placeTower(2,NORMCREEPTOWER, 12, 3);
	
	setNodemap();


	/*
	spawnCreep(2,1,1,Bases[1]);
	spawnCreep(1,2,1,Bases[0]);
	spawnCreep(1,3,1,Bases[0]);
	spawnCreep(2,0,1,Bases[1]);
	*/

	int run = 1;
	int nc = 0;

	FPS_Regulator *reg = new FPS_Regulator(MAX_FPS);

	cListNode<creep*> *cur = NULL;
	cListNode<structure*> *curTower = NULL;
	cListNode<creep*> *temp = NULL;
	while(run)
	{
		reg->start();

		p1Spawner->iterate();
		p2Spawner->iterate();

		for(curTower = towerList.getStart(); curTower != NULL; curTower = curTower->getNext())
			curTower->getData()->iterate();

		for(cur = creepList.getStart(); cur != NULL;)
		{ //loop through the list
			if(cur->getData()->move()) //move each creep in the list
			{
				if(players[cur->getData()->getPlayer() - 1].takeDamage())
				{
					cout << "game over man, game over...\n";
					system("pause");
				}
				cur->getData()->kill(); 



				sendMessageToQueue(UpdMess(cur->getData()->getPlayer(), PLAYERUPDATE, getPlayer(cur->getData()->getPlayer())->getHealth(), getPlayer(cur->getData()->getPlayer())->getMoney()).getMT());
			}
			else
			{
				//do any additional operations on creeps here, ie health regen, burning, poison, random splitting etc
				sendMessageToQueue(UpdMess(cur->getData()->getPlayer(),CREEP,cur->getIndex(),cur->getData()->getX(),cur->getData()->getY(),cur->getData()->getHealth()).getMT());
				cout << cur->getData()->getX() << " " << cur->getData()->getY() << "\n";
			}
			
			temp = cur;
			cur = cur->getNext();
			if(temp->getData()->isAlive() == false)
			{
				sendMessageToQueue(UpdMess(temp->getData()->getPlayer(),CREEP,temp->getIndex(),0,0,0).getMT());
				creepList.deleteNode(temp->getIndex());
			}
		}
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

void game_host::updatePaths()
{
	/*cListNode<creep*> *cur = NULL;
	cur = creepList.getStart();
	while (cur != NULL)
	{
		cur->getData()->recalcPath(Nodemap);
		cur = cur->getNext();
	}*/

	for (cListNode<creep*> *cur = creepList.getStart(); cur != NULL; cur = cur->getNext())
	{
		cur->getData()->recalcPath(Nodemap);
	}
}

void game_host::spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord){
	creep *newCreep = new creep(creepType, playerNumber, creepLevel, spawnCoord.x, spawnCoord.y);
	//newCreep->p.setStart(spawnCoord);
	int nIndex;
	if(playerNumber == 1)
	{
		newCreep->p.setGoal(Bases[1]);
		newCreep->p.genPath(Nodemap);
		nIndex = creepList.insertInOrder(newCreep);
	}
	else
	{
		newCreep->p.setGoal(Bases[0]);
		newCreep->p.genPath(Nodemap);
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
	if(Tmap[x][y] == NULL)
	{
		if(towerType == STRUCTURE)
		{
			if(Tmap[x][y] == NULL)
			{
				if(2 <= this->getPlayer(playerNumber)->getMoney())
				{
					structure *newStructure = new structure(STRUCTURESTARTLEVEL, playerNumber, towerType, x, y);
					this->getPlayer(playerNumber)->spendMoney(2);
					this->towerList.insertInOrder(newStructure);
					Tmap[x][y] = newStructure;
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else if(towerType >= NORMTOWER && towerType <= MINETOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Standard_Tower *newTower = new Standard_Tower(STANDARDTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= this->getPlayer(playerNumber)->getMoney())
				{
					this->getPlayer(playerNumber)->spendMoney(newTower->getCost());
					this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else
					return 0;
			}
			else return 0;
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
					this->towerList.insertInOrder(newTower);
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

		setNodemap();
		updatePaths();
		sendMessageToQueue(UpdMess(playerNumber, TOWER, TOWERCREATION, 42, x, y, towerType).getMT());
		return 1;
	}
	else
		return 0;
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