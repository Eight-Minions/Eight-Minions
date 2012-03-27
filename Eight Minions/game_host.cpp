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
	setNodemap();

	creep testCreep(1,1,p1Base.x,p1Base.y);

	testCreep.p.setStart(p1Base);
	testCreep.p.setGoal(p2Base);
	testCreep.p.genPath(Nodemap);

	int run = 1;
	int nc = 0;

	//

	//
	int now;
	while(run)
	{
		//receive input
		//process input
		
		/*nc = creepList1.getSize();
		for(int i = 0; i < nc; i++)
		{
			creepList1.getObjectWithID(i).move();
		}
		nc = creepList2.getSize();
		for(int i = 0; i < nc; i++)
		{
			creepList2.getObjectWithID(i).move();
		}*/

		/*<movement testing>
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
		</movement testing>*/

		

		now = SDL_GetTicks();
		for(int i = 0; i < 10; i++)
			sendtop1UDP("test message");
		cout << recieveMessagep1() << "\n";
		cout << SDL_GetTicks() - now << " milliseconds\n";
		system("pause");
		return 1;
		//<awesome idea>
		//maybe combine update strings together separated by some sentinel character
		//that way we need to send less individual packets (which may make a difference when we have tons and tons of creeps/towers
		// </awesome idea>

		/*
		foreach tower
		do->attack
		send updates
		*/

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
	
}


