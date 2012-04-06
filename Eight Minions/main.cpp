#include "game_host.h"
#include "client.h"

int main(int argc, char* argv[]){
	cout << "Build 0.13\n\n";
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
		cout << "Not testing anything...\n";
		string tower = UpdMess(1, TOWER, 1234, 2 , 1, 1).getMT();
		cout << tower << endl;
		UpdMess t(tower);
		cout << "Player :" <<  t.getPlayer() << " Type: " << t.getType() << " X: " << t.getVal(0) << " Y: " << t.getVal(1) << " Type: " << t.getVal(2) << endl;

	}
	else if(c == 4)
	{
		cout << "To do list:\n";
		cout << ">change the creeps so that the creeps dont load their own images\n\tinstead, have the client load them all\n";
		cout << ">send towers so client displays them\n";
		cout << ">Tower messages dont work quite right\n";
		cout << ">find a way to keep track of players, money, health, upgrades, etc\n";
		cout << ">some sort of 'wave' object that manages spawning creeps and\n\t can be adjusted for difficulty, purchases, upgrades, etc\n";
		cout << ">once we have more creeps and towers and things happening\n\ttest increasing the maximum UDP message length\n";
		cout << ">clean out old commented code\n";
		cout << ">make client throw out all creeps every so often and remake them as they receive updates\n\tthis ensures no artifacts\n";
		cout << ">low precedence: search for memory leaks\n";
	}
	system("pause");
	return 0;
}