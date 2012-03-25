#include "path.h"

Path::Path()
{
	//start VERY bad coding
	mapsize.x = 35;
	mapsize.y = 21;
	//end VERY bad coding
}

Path::Path(int x, int y)
{
	this->Nodemap.resize(x);
	for(int i = 0; i < x; i++)
	{
		this->Nodemap[i].resize(y);
	}
	mapsize.x = x;
	mapsize.y = y;
}

int Path::numPaths(coord c)
{
	int n = 0;
	if(c.x > 0 && Nodemap[c.x - 1][c.y] == 0)
		n++;
	if(c.y > 0 && Nodemap[c.x][c.y - 1] == 0)
		n++;
	if(c.x < mapsize.x - 1 && Nodemap[c.x + 1][c.y] == 0)
		n++;
	if(c.y	< mapsize.y - 1 && Nodemap[c.x][c.y + 1] == 0)
		n++;
	return n;
}

coord Path::move(coord cur)
{
	queue<coord> opt;
	double mindis = 100;
	double dis;
	coord temp;
	if(cur.x < mapsize.x - 1 && Nodemap[cur.x + 1][cur.y] == 0)
	{
		coord n = {cur.x + 1, cur.y};
		opt.push(n);
	}

	if(cur.x > 0 && Nodemap[cur.x - 1][cur.y] == 0)
	{
		coord n = {cur.x - 1, cur.y};
		opt.push(n);
	}

	if(cur.y < mapsize.y - 1 && Nodemap[cur.x][cur.y + 1] == 0)
	{
		coord n = {cur.x, cur.y + 1};
		opt.push(n);
	}

	if(cur.y > 0 && Nodemap[cur.x][cur.y - 1] == 0)
	{
		coord n = {cur.x, cur.y - 1};
		opt.push(n);
	}

	while(!opt.empty())
	{
		temp = opt.front();
		dis = sqrt(pow((double)temp.x - start.x,2) + pow((double)temp.y - start.y,2));
		if(dis < mindis)
		{
			cur = temp;
			mindis = dis;
		}
		opt.pop();
	}
	return cur;
}

int Path::genPath(vector<vector<bool>> nMap)
{
	//insert super fast efficient algorithm for finding the fastest route from the start to the finish
	//1 = impassable, 0 = passable
	Nodemap = nMap;
	coord cur = goal;
	int paths;
	p.push(cur);
	while(!(cur.x == start.x && cur.y == start.y)  && !p.empty())
	{
		paths = numPaths(cur);
		if(paths == 0)
		{
			return -1;
		}
		else if(paths == 1)
		{
			Nodemap[cur.x][cur.y] = 1;
			cur = p.top();
			p.pop();
		}
		//move towards goal in some way.
		if(paths > 1)
		{
			cur = move(cur);
			p.push(cur);
		}
	}
	if(!(cur.x == start.x && cur.y == start.y))
		return -1;
	else
	{
		p.pop();
		while(!p.empty())
		{
			fPath.push(p.top());
			p.pop();
		}
	}
	return 1;
}


void Path::setStart(coord s)
{
	start = s;
}

void Path::setGoal(coord g)
{
	goal = g;
}

coord Path::getNext()
{
	return fPath.front();
}

bool Path::isEmpty()
{
	return fPath.empty();
}

void Path::pop()
{
	fPath.pop();
}
