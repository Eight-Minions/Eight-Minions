#include "game_host.h"
#include "client.h"

int main(int argc, char* argv[]){
	
	printf("Host or Connect to host? (host-1, connect-2)\n>");
	int c = 0;
	cin >> c;
	if(c == 1)
	{
		unsigned int port;
		game_host server;
		cout << "enter port to host on:";
		cin >> port;
		//error check this number
		server.setPort(port);
		//do other server things, namely...
		server.run();
	}
	if(c == 2)
	{
		string addr;
		unsigned int port;
		client player;
		cout << "Address of server:";
		cin >> addr;
		cout << "port of server:";
		cin >> port;
		player.setPort(port);
		player.setServerAddress(addr);
		if(player.connectToServer() == CONNECTION_SUCCESSFUL)
			player.run();
		else
			cout << "connection failed\n";
	}
	return 0;
}