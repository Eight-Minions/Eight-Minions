#include "game_host.h"
#include "client.h"

int main(int argc, char* argv[]){
	cout << "Build 0.48\n\n";
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

		Standard_Tower a(1,1,1,2,3);
		//Tower Attack:	UpdMess(Player[1], TOWERATTACK, AttackerX[2], AttackerY[2], AttackedID[4], AttackType[2]);
		UpdMess *j =  new UpdMess(a.getPlayer(), TOWERATTACK, a.getX(), a.getY(), 1234, 2);
		cout << j->getMT() << endl;
		UpdMess n(j->getMT());
		cout << "P: " << n.getPlayer() << " X: " << n.getVal(0) << " Y: " << n.getVal(1) << " ID: " << n.getVal(2) << endl;
		/* 
		creep a(1,1,1,3,4);
		//UpdMess(Player[1], NEWCREEP, CreepID[4], X[4], Y[4], Health[5], Type[2], Level[3]);
		UpdMess um(1, NEWCREEP, 1, a.getX(), a.getY(), a.getHealth(), a.getType(), a.getLevel());
		cout << um.getMT();
		cout << "Testing mode started...\n";
		cout << "Now testing the button creation\n";
		client testt;
		testt.initButtons();
		*/

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