#include "game_host.h"
#include "client.h"

int main(int argc, char* argv[]){
	cout << "Build 0.11\n\n";
	cout << "Host or Connect to host? (host-1, connect-2) SOMEONE BUILD A NICER MENU\n>";
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
		cout << "port set\n";
		//do other server things, namely...
		server.testrun();
		cout << "finished running\n";
	}
	else if(c == 2)
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
			player.testrun();
		else
			cout << "connection failed\nexiting program...\n";
	}
	else if(c == 3)
	{
		cout << "Testing mode started...\n";
		cout << "Now testing update message...\n";

		UpdMess n(1,1,506,256,3);
		//( int t, int pl, int ida, int idb, int atype )
		cout << n.getMT() << "\n";

	}
	else if(c == 4)
	{
		cout << "To do list:\n";
		cout << ">change the creeps so that the creeps dont load their own images\n\tinstead, have the client load them all\n";
		cout << ">send towers so client displays them\n";
		cout << ">resolve problem with the lists, (server has only one while client has two\n\tcauses id finding problems)\n";
		cout << ">find a way to keep track of players, money, health, upgrades, etc\n";
	}
	system("pause");
	return 0;
}