#include "client.h"

int main(int argc, char* argv[])
{
	int c = 0;
	cout << "1) Single Player\n2) Two Player\n";
	cin >> c;
	if(c == 1)
	{
		client player;
		player.run(true);
	}
	if(c == 2)
	{
		string addr;
		client player;
		cout << "Address of server:";
		cin >> addr;
		player.setPort(5064);
		player.setServerAddress(addr);
		if(player.connectToServer() == CONNECTION_SUCCESSFUL)
			player.run(false);
		else
			cout << "connection failed\nexiting program...\n";
	}
	return 0;
}