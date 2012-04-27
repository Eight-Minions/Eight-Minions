#include "path.h"

Path::Path()
{
	mapsize.x = MAPSIZE_X;
	mapsize.y = MAPSIZE_Y;
}

/*
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
				//h = (aStar[i].pathLength * aStar[i].pathLength) + aStar[i].aproxLengthToGoal;
				if (aStar[i].hueristic < min_h)
				{
					sel = i;
					min_h = aStar[i].hueristic;
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
*/

int Path::genPath(vector<vector<bool> > nMap, int recalc)
{
	aStarNode *cur;
	Nodemap = nMap;
	openList.clear();
	closedList.clear();
	openList.push_front(makeAstar(start,NULL,0,intDist(start, goal.x, goal.y)));
	if(recalc == 2)
	{
		cur = openList.front();
		openList.pop_front();
		closedList.push_front(cur);
		openList.push_front(makeAstar(specRecalc,cur,1,intDist(specRecalc, goal.x, goal.y)));
	}
	
	do 
	{
		cur = openList.front();
		openList.pop_front();
		closedList.push_front(cur);
	} while (!expand(cur) && !openList.empty());
	
	if(closedList.front()->self.x != goal.x || closedList.front()->self.y != goal.y)
	{
		return 0;
	}
	fPath.clear();

	cur = closedList.front();

	while(cur != NULL)
	{
		fPath.push_back(cur->self);
		cur = cur->parentPtr;
	}
	if(recalc != 1)
		pop();

	return 1;
}

bool Path::expand( aStarNode *n)
{
	int temp = n->self.x - 1;
	aStarNode* next = NULL;
	if(n->self.x >= 1 && Nodemap[temp][n->self.y] == false)
	{
		Nodemap[temp][n->self.y] = true;
		int dist = intDist(goal, temp, n->self.y);
		next = makeAstar(gC(temp, n->self.y),n,n->pathLength + 1, dist);
		if(dist == 0)
		{
			//goal found, stop.
			
			return true;
		}
		else
			insertInOrder(next);
	
	}
	temp = n->self.x + 1;
	if(n->self.x < MAPSIZE_X - 1 && Nodemap[temp][n->self.y] == false)
	{
		Nodemap[temp][n->self.y] = true;
		int dist = intDist(goal,temp, n->self.y);
		next = makeAstar(gC(temp, n->self.y),n,n->pathLength + 1, dist);
		if(dist == 0)
		{
			//goal found, stop.
			closedList.push_front(next);
			return true;
		}	
		else
			insertInOrder(next);
	}
	temp = n->self.y  - 1;
	if(n->self.y >= 1 && Nodemap[n->self.x][temp] == false)
	{
		Nodemap[n->self.x][temp] = true;
		int dist = intDist(goal, n->self.x, temp);
		next = makeAstar(gC(n->self.x, temp),n,n->pathLength + 1, dist);
		if(dist == 0)
		{
			//goal found, stop.
			closedList.push_front(next);
			return true;
		}		
		else
			insertInOrder(next);
	}
	temp = n->self.y + 1;
	if(n->self.y < MAPSIZE_Y - 1 && Nodemap[n->self.x][temp] == false)
	{
		Nodemap[n->self.x][temp] = true;
		int dist = intDist(goal, n->self.x, temp);
		next = makeAstar(gC(n->self.x,temp),n,n->pathLength + 1, dist);
		if(dist == 0)
		{
			//goal found, stop.
			closedList.push_front(next);
			return true;
		}	
		else
			insertInOrder(next);
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

aStarNode* makeAstar(coord self, aStarNode* nParent, int Nlength, int nTogo)
{
	aStarNode *n = new aStarNode;
	n->self = self;
	n->parentPtr = nParent;
	n->pathLength = Nlength;
	n->aproxLengthToGoal = nTogo;
	n->expanded = false;
	//n.parent_index = parent_i;
	n->hueristic = (n->pathLength * n->pathLength) + n->aproxLengthToGoal;
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

void Path::insertInOrder(aStarNode *nNode)
{
	for(list<aStarNode*>::iterator i = openList.begin(); i != openList.end(); i++)
	{
		if(nNode->hueristic < (*i)->hueristic)
		{
			openList.insert(i,nNode);
			return;
		}
	}
	openList.push_back(nNode);
}

void Path::setSpec( coord s )
{
	specRecalc.x = s.x;
	specRecalc.y = s.y;
}
