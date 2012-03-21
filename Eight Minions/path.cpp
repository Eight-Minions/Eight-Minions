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
	int n = 0;
	if(c.x >= 0 && Nodemap[c.x - 1][c.y] == 0)
		n++;
	if(c.y >= 0 && Nodemap[c.x][c.y - 1] == 0)
		n++;
	if(c.x < mapsize.x && Nodemap[c.x + 1][c.y] == 0)
		n++;
	if(c.y	< mapsize.y && Nodemap[c.x][c.y + 1] == 0)
		n++;
	return n;
}

int Path::genPath()
{
	//insert super fast efficient algorithm for finding the fastest route from the start to the finish
	//1 = impassable, 0 = passable
	coord cur = goal;
	int paths, int dx, dy;
	p.push(cur);
	while(cur != start && !p.empty())
	{
		paths = numPaths(cur);
		if(paths == 0)
		{
			return -1;
		}
		if(paths == 1)
		{
			Nodemap[c.x][c.y] = 1;
			cur = p.top();
			p.pop();
		}
		//move towards goal in some way.
		dx = goal.x - cur.x;
		dy = goal.y - cur.y;
		if(abs(dx) > abs(dy))
		{
			if(dx == abs(dx))
			{
				
			}
		}
		


	}
	if(cur != start)
		return -1;
	else
	{
		//add path to some sort of list...
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