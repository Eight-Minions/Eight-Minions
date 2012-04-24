#include "path.h"

Path::Path()
{
	mapsize.x = MAPSIZE_X;
	mapsize.y = MAPSIZE_Y;
}

int Path::genPath(vector<vector<bool> > nMap, bool recalc)
{
	Nodemap = nMap;
	aStar.clear();
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
		//aStar.erase(aStar.begin() + sel);
		//sel = -1;
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
		//if(sel == -1)
		if(min_h == 100000)
		{
			//cout << "no avaliable path\n";
			fPath.clear();
			return 0;
		}

	} while (!expand(aStar[sel], sel));

	fPath.clear();
	aStarNode temp = aStar[aStar.size() - 1];
	fPath.push_back(temp.self);
	do 
	{
		temp = aStar[temp.parent_index];
		fPath.push_back(temp.self);
	}while(temp.parent.x != -1);
	if(!recalc)
		pop();
	return 1;

}

bool Path::expand( aStarNode n, int n_index)
{
	int temp = n.self.x - 1;
	if(n.self.x >= 1 && Nodemap[temp][n.self.y] == false)
	{
		Nodemap[temp][n.self.y] = true;
		int dist = intDist(goal, temp, n.self.y);
		aStar.push_back(makeAstar(gC(temp, n.self.y),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}		
	}
	temp = n.self.x + 1;
	if(n.self.x < MAPSIZE_X - 1 && Nodemap[temp][n.self.y] == false)
	{
		Nodemap[temp][n.self.y] = true;
		int dist = intDist(goal,temp, n.self.y);
		aStar.push_back(makeAstar(gC(temp, n.self.y),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}	
	}
	temp = n.self.y  - 1;
	if(n.self.y >= 1 && Nodemap[n.self.x][temp] == false)
	{
		Nodemap[n.self.x][temp] = true;
		int dist = intDist(goal, n.self.x, temp);
		aStar.push_back(makeAstar(gC(n.self.x, temp),n.self,n.pathLength + 1, dist, n_index));
		if(dist == 0)
		{
			//goal found, stop.
			return true;
		}		
	}
	temp = n.self.y + 1;
	if(n.self.y < MAPSIZE_Y - 1 && Nodemap[n.self.x][temp] == false)
	{
		Nodemap[n.self.x][temp] = true;
		int dist = intDist(goal, n.self.x, temp);
		aStar.push_back(makeAstar(gC(n.self.x,temp),n.self,n.pathLength + 1, dist, n_index));
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
	return fPath[fPath.size() - 1];
}

bool Path::isEmpty()
{
	return fPath.empty();
}

void Path::pop()
{
	fPath.pop_back();
}

void Path::setNodemap( vector<vector<bool> > nMap )
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