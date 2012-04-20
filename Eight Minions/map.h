#ifndef MAP_H
#define MAP_H

#include "resources.h"
#include "game_host.h"

class Map
{
public:
	Map();
	void load(string filename);
	bool verify();
	string getMapName();

private:
	string mapname;
	vector<coord*> objectLocations;
};
#endif