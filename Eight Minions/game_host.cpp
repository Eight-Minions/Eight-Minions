#include "game_host.h"

int game_host::init()
{
	Tmap.resize(MAPSIZE_X);
	Nodemap.resize(MAPSIZE_X);
	for(int i = 0; i < MAPSIZE_X;i++)
	{
		Tmap[i].resize(MAPSIZE_Y);
		Nodemap[i].resize(MAPSIZE_Y);
	}
	p1Base.x = 0;
	p1Base.y = 10;
	p2Base.x = 34;
	p2Base.y = 10;

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
	this->waitForClient_test();
	
	//this->waitForClients();
	//this->sendToClients("testing!!!");
	Tmap[4][10] = new tower(500,2,3,4,10);
	Tmap[3][11] = new tower(500,2,3,3,11);
	Tmap[5][9] = new tower(300,2,3,5,9);
	setNodemap();

	creep testCreep(1,1,p1Base.x,p1Base.y);

	testCreep.p.setStart(p1Base);
	testCreep.p.setGoal(p2Base);
	testCreep.p.genPath(Nodemap);

	int run = 1;
	int nc = 0;
	cListNode<creep> *cur = NULL;

	int now;
	while(run)
	{
		//receive input
		//receiveMessagesToQueue
		//process input
		//go through message queue and decide what to do for each one
		
		//<test code>
		if(testCreep.move())
		{
			cout << "end\n";
			return 1;
		}
		else
		{
			cout << testCreep.getX() << " " << testCreep.getY() << "\n";
		}
		sendtop1UDP(UpdMess(1,1,23,testCreep.getX(),testCreep.getY(),100).getMT());
		//</test code>	



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

		cur = creepList1.getStart(); //get the head of player ones creep list
		while(cur != NULL){ //loop through the list
			cur->getData().move(); //move each creep in the list
			//do any additional operations on creeps here, ie health regen, burning, poison, random splitting etc
			sendMessageToQueue(UpdMess(1,1,cur->getIndex(),cur->getData().getX(),cur->getData().getY(),cur->getData().getHealth()).getMT());
			cur = cur->getNext(); //move to next creep in list
		}
		cur = creepList2.getStart();
		while (cur != NULL){
			cur->getData().move();
			cur = cur->getNext();
		}



		sendMessageToQueue("SEND"); //this to ensure that all updates for this pass are sent
		SDL_Delay(30); //approx 30 times/second maybe reduce to 10?
	}

	return 0;
}

void game_host::setNodemap()
{
	for(int i = 0; i < MAPSIZE_X; i++)
	{
		for(int j = 0; j < MAPSIZE_Y; j++)
		{
			Nodemap[i][j] = (Tmap[i][j] != NULL);
		}
	}
}

void game_host::updatePaths()
{
	cListNode<creep> *cur = NULL;
	cur = creepList1.getStart();
	while (cur != NULL){
		cur->getData().recalcPath(Nodemap);
		cur = cur->getNext();
	}
	cur = creepList2.getStart();
	while (cur != NULL){
		cur->getData().recalcPath(Nodemap);
		cur = cur->getNext();
	}
}

void game_host::spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord){
	if(playerNumber == 1)
		creepList1.insertInOrder(creep(creepType, creepLevel, spawnCoord.x, spawnCoord.y));
	else
		creepList2.insertInOrder(creep(creepType, creepLevel, spawnCoord.x, spawnCoord.y));
}