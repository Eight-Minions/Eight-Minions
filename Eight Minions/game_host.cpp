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

	int r = 1;
	int x = 10;
	int change = 1;
	int y = 10;
	int changey = 1;
	string n;
	char q[16];
	while(r)
	{
		/*if(SDLNet_CheckSockets(socketset,1) > 0 )
		{
			if(SDLNet_SocketReady(player1sd))
			{
				cout << this->recieveMessagep1() << "\n";
			}
			if(SDLNet_SocketReady(player2sd))
			{
				cout << this->recieveMessagep2() << "\n";
			}
		}*/

		
		x += change;
		if(x > 400)
			change = -1;
		if(x < 1)
			change = 1;

		y += changey;
		if( y > 300)
			changey = -1;
		if(y < 1)
			changey = 1;

		
		this->sendUpdate(0,0,1,x);
		this->sendUpdate(0,0,2,y);
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
		if(testCreep.move())
		{
			cout << "end\n";
			return 1;
		}
		cout << testCreep.getX() << " " << testCreep.getY() << "\n";
		sendtop1UDP("testing");

		/*
		foreach tower
		do->attack
		send updates
		*/

		//SDL_Delay(30); //approx 30 times/second maybe reduce to 10?
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


