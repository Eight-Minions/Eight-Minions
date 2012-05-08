#ifndef PATH_H
#define PATH_H
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <math.h>

#ifndef MAPSIZE_X
#define MAPSIZE_X 26
#endif

#ifndef MAPSIZE_Y
#define MAPSIZE_Y 20
#endif
using std::vector;
using std::stack;
using std::queue;
using std::list;

typedef struct coord
{
	int x, y;
}coord;

typedef struct aStarNode
{
	coord parent;
	aStarNode* parentPtr;
	int parent_index;
	coord self;
	int pathLength;
	int aproxLengthToGoal;
	int hueristic;
	bool expanded;
}aStarNode;

class Path
{
private:
	vector<vector<bool> > Nodemap;
	coord start;
	coord specRecalc;
	coord goal;
	stack<coord> p;
	coord mapsize;
	vector<aStarNode> aStar;
	list<aStarNode*> openList;
	list<aStarNode*> closedList;
public:
	Path();
	Path(int x, int y);

	vector<coord> fPath;

	int genPath(vector<vector<bool> > nMap, int recalc);
	bool expand( aStarNode *n);
	coord move(coord cur); //possibly redundant at this point.
	void setStart(coord s);
	void setSpec(coord s);
	void setGoal(coord g);
	void setNodemap(vector<vector<bool> > nMap);
	int numPaths(coord c);
	queue<coord> getPath();
	coord getNext();
	bool isEmpty();
	void pop();
	void insertInOrder(aStarNode *nNode);
};

aStarNode* makeAstar(coord nSelf, aStarNode *nParent, int Nlength, int nTogo);
coord gC( int x, int y );
int intDist(coord a, int x, int y); //for the A* algorithm
#endif