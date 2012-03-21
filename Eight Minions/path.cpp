#include "path.h"

Path::Path(int x, int y)
{
	this->Nodemap.resize(x);
	for(int i = 0; i < x; i++)
	{
		this->Nodemap[i].resize(y)
	}
	mapsize.x = x;
	mapsize.y = y;
}

int Path::numPaths(coord c)
{

}

int Path::genPath()
{
	//insert super fast efficient algorithm for finding the fastest route from the start to the finish
	//1 = impassable, 0 = passable
	coord cur = goal;
	p.push(cur);
	while(cur != start)
	{
		
	}
	return 1;
}

void Path::setNodeMap()
{
	//accept some sort of input and generate a node map of 0's and 1's that say whether or not that space is 
	//traversable
}

void Path::setStart(int x, int y)
{
start.x = x;
start.y = y;
}

void Path::setGoal(int x, int y)
{
	goal.x = x;
	goal.y = y;
}