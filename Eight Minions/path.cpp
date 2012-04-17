#include "path.h"

Path::Path()
{
	mapsize.x = MAPSIZE_X;
	mapsize.y = MAPSIZE_Y;
}

/*Path::Path(int x, int y)
{
this->Nodemap->resize(x);
for(int i = 0; i < x; i++)
{
this->Nodemap[i].resize(y);
}
mapsize.x = x;
mapsize.y = y;
}*/

/*int Path::numPaths(coord c)
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
}*/

/*coord Path::move(coord cur)
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
}*/

/*
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
}*/

int Path::genPath(vector<vector<bool>> nMap)
{
	Nodemap = nMap;
	aStar.push_back(makeAstar(start,gC(-1,-1),0,intDist(start, goal.x, goal.y), -1));
	Nodemap[start.x][start.y] = true;
	expand(aStar[0],0);
	int i = 0;
	int sel = 0;
	int min_h = 100000;
	int h = 0;
	do 
	{
		aStar[sel].expanded = true;
		sel = -1;
		min_h = 100000;
		for(i = 0; i < aStar.size(); i++)
		{
			if(!aStar[i].expanded)
			{
				h = (aStar[i].pathLength * aStar[i].pathLength) + aStar[i].aproxLengthToGoal;
				if (h < min_h)
				{
					sel = i;
					min_h = h;
				}
			}
		}
		if(sel == -1)
		{
			//cout << "no avaliable path\n";
			return 0;
		}

	} while (!expand(aStar[sel], sel));

	aStarNode temp = aStar[aStar.size() - 1];
	fPath.push(temp.self);
	do 
	{
		temp = aStar[temp.parent_index];
		fPath.push(temp.self);
	}while(temp.parent.x != -1);
	pop();
	return 1;

}

bool Path::expand( aStarNode n, int n_index)
{
	if(n.self.x >= 1 && Nodemap[n.self.x - 1][n.self.y] == false)
	{
		Nodemap[n.self.x - 1][n.self.y] = true;
		int dist = intDist(goal, n.self.x - 1, n.self.y);
		aStar.push_back(makeAstar(gC(n.self.x - 1, n.self.y),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}		
	}
	if(n.self.x < MAPSIZE_X - 1 && Nodemap[n.self.x + 1][n.self.y] == false)
	{
		Nodemap[n.self.x + 1][n.self.y] = true;
		int dist = intDist(goal, n.self.x + 1, n.self.y);
		aStar.push_back(makeAstar(gC(n.self.x + 1, n.self.y),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}	
	}
	if(n.self.y >= 1 && Nodemap[n.self.x][n.self.y  - 1] == false)
	{
		Nodemap[n.self.x][n.self.y  - 1] = true;
		int dist = intDist(goal, n.self.x, n.self.y - 1);
		aStar.push_back(makeAstar(gC(n.self.x, n.self.y - 1),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}		
	}
	if(n.self.y < MAPSIZE_Y - 1 && Nodemap[n.self.x][n.self.y + 1] == false)
	{
		Nodemap[n.self.x][n.self.y + 1] = true;
		int dist = intDist(goal, n.self.x,n.self.y + 1);
		aStar.push_back(makeAstar(gC(n.self.x,n.self.y + 1),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}	
	}
	return false;
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
	return fPath.top();
}

bool Path::isEmpty()
{
	return fPath.empty();
}

void Path::pop()
{
	fPath.pop();
}

void Path::setNodemap( vector<vector<bool>> nMap )
{
	Nodemap = nMap;
}



aStarNode makeAstar(coord self, coord nParent, int Nlength, int nTogo , int parent_i)
{
	aStarNode n;
	n.self = self;
	n.parent = nParent;
	n.pathLength = Nlength;
	n.aproxLengthToGoal = nTogo;
	n.expanded = false;
	n.parent_index = parent_i;
	return n;
}

int intDist( coord a, int x, int y )
{
	return ((a.x - x) * (a.x - x)) + ((a.y - y) * (a.y - y));
}

coord gC( int x, int y )
{
	coord n = {x,y};
	return n;
}