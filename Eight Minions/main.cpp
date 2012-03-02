#include "resources.h"

int main(void){
	
	printf("Host or Connect to host? (host-1, connect-2)\n>");
	int c = 0;
	cin >> c;
	if(c == 1)
	{
		unsigned int port;
		game_host server;
		printf("enter port to host on:");
		cin >> port;
		//error check this number
		server.setPort(port);
		//do other server things, namely...
		server.run();
	}
	if(c == 2)
	{
		string addr;
		client player;


	}
	return 0;
}