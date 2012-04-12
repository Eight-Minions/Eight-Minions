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
	p1Spawner = new Spawner(this, 1, false);
	p2Spawner = new Spawner(this, 2, false);
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
	this->waitForClients();
	//this->waitForClient_test();

	placeTower(1,1,4,9);
	placeTower(1,1,11,11);
	placeTower(1,1,3,9);
	placeTower(1,1,15,8);
	placeTower(1,1,14,9);
	placeTower(1,1,5,10);
	setNodemap();

	spawnCreep(1,2,1,Bases[0]);
	spawnCreep(1,3,1,Bases[0]);
	spawnCreep(2,1,1,Bases[1]);
	spawnCreep(2,2,2,Bases[1]);

	int run = 1;
	int nc = 0;
	cListNode<creep*> *cur = NULL;

	while(run)
	{
		//receive input
		//receiveMessagesToQueue
		//process input
		//go through message queue and decide what to do for each one

		/*
		foreach tower
		pick attack
		do attack
		send updates
		note: attacks should be on a time delay, and possibly something like this:
		tower picks target, waits Nms
		tower starts attack
		attack takes Nms
		attack hits, creep takes damage
		now tower waits until its attack recharges before it can attack again
		*/

		cur = creepList.getStart(); //get the head of player ones creep list
		while(cur != NULL){ //loop through the list
			if(cur->getData()->move()) //move each creep in the list
			{
				int i = cur->getIndex();

				players[cur->getData()->getPlayer() - 1].takeDamage();

				cur = cur->getNext(); //move to next creep in list
				creepList.deleteNode(i);
			}
			else
			{
				//do any additional operations on creeps here, ie health regen, burning, poison, random splitting etc
				sendMessageToQueue(UpdMess(cur->getData()->getPlayer(),CREEP,cur->getIndex(),cur->getData()->getX(),cur->getData()->getY(),cur->getData()->getHealth()).getMT());
				cout << cur->getData()->getX() << " " << cur->getData()->getY() << "\n";
				cur = cur->getNext(); //move to next creep in list
			}
		}
		sendMessageToQueue("SEND"); //this to ensure that all updates for this pass are sent*/
		SDL_Delay(30); //approx 30 times/second maybe reduce to 10?
	}
	return 0;
}

void game_host::setNodemap()
{
	for(int i = 0; i < MAPSIZE_X; i++)
		for(int j = 0; j < MAPSIZE_Y; j++)
			Nodemap[i][j] = (Tmap[i][j] != NULL);
}

void game_host::updatePaths()
{
	cListNode<creep*> *cur = NULL;
	cur = creepList.getStart();
	while (cur != NULL){
		cur->getData()->recalcPath(Nodemap);
		cur = cur->getNext();
	}
}

void game_host::spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord){
	creep *newCreep = new creep(creepType, playerNumber, creepLevel, spawnCoord.x, spawnCoord.y);
	newCreep->p.setStart(spawnCoord);
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

int game_host::placeTower( int playerNumber, int towerType, int x, int y)
{
	if(Tmap[x][y] == NULL)
	{
		Tmap[x][y] = new tower(0, playerNumber, towerType,x,y);
		setNodemap();
		updatePaths();
		sendMessageToQueue(UpdMess(playerNumber, TOWER,42, x,y,towerType).getMT());
		return 1;
	}
	else
		return 0;
}
cList<creep*> *game_host::getCreepList()
{
	return &creepList;
}