#include "map.h"

Map::Map()
{
	mapname = "No Map";
}

string Map::getMapName()
{
	return mapname;
}
void Map::load(string filename)
{
	ifstream input;
	input.open(filename.c_str(),ifstream::in); 
	if(input!= NULL)
	{

	}
	else
	{
		cout << "File not found, unable to load" << endl;	
	}
	input.close();
}
bool verify()
{
	return true;
}