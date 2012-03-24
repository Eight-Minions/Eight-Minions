#include "game_host.h"


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
	//this->init();
	//this->waitForClients();
	//this->sendToClients("testing!!!");

	int run = 1;
	
	while(run)
	{
		//receive input
		//process input
		

		SDL_Delay(30);
	}

	return 0;
}


