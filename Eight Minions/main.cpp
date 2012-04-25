#include "game_host.h"
#include "client.h"

int main(int argc, char* argv[])
{
	cout << "Build 0.64\n\n";
	cout << "Host or Connect to host? (host-1, connect-2) SOMEONE BUILD A NICER MENU\n>";
	int c = 0;
	cin >> c;
	if(c == 1 || c == 9)
	{
		unsigned int port;

		game_host server;
		cout << "enter port to host on:";
		cin >> port;
		//error check this number
		server.setPort(port);
		cout << "port set\n";
		//do other server things, namely...
		if(c == 9)
			server.run(true);
		else
			server.run(false);
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
			player.run();
		else
			cout << "connection failed\nexiting program...\n";
	}
	else if(c == 3)
	{
		const int largeNumber = 105;
		cList<int> testList;
		list<int> usedIDs;
		for(int i = 0; i < largeNumber; i++)
		{	
			usedIDs.push_front(testList.insertInOrder(i));
		}
		while(usedIDs.empty() != true)
		{
			cout << "ID: " << usedIDs.front() << " Data: " << testList.getNodeWithID(usedIDs.front())->getData()<< endl;
			usedIDs.pop_front();
		}
	}
	else if(c == 4)
	{
		cout << "To do list:\n";
		cout << ">allow for players to place towers\n";
		cout << ">change the creeps so that the creeps dont load their own images\n\tinstead, have the client load them all\n";
		cout << ">find a way to keep track of players, money, health, upgrades, etc\n";
		cout << ">once we have more creeps and towers and things happening\n\ttest increasing the maximum UDP message length\n";
		cout << ">clean out old commented code\n";
		cout << ">make client throw out all creeps every so often and remake them as they receive updates\n\tthis ensures no artifacts\n";
		cout << ">low precedence: search for memory leaks\n";
		cout << ">rewrite connection function, make more readable and less ugly\n";
	}
	system("pause");
	return 0;
}