#include "game_host.h"

int main(int argc, char* argv[])
{
	game_host server;
	server.setPort(5064);
	server.run(true);
	cout << "finished  running \n";
	return 0;
}