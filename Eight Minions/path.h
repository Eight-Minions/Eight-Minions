#ifndef PATH_H
#define PATH_H
#include <vector>
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

typedef struct coord
{
	int x, y;
}coord;

typedef struct aStarNode
{
	coord parent;
	int parent_index;
	coord self;
	int pathLength;
	int aproxLengthToGoal;
	bool expanded;
}aStarNode;

class Path
{
private:
	vector<vector<bool>> Nodemap;
	coord start;
	coord goal;
	stack<coord> p;
	coord mapsize;
	stack<coord> fPath;
	vector<aStarNode> aStar;
public:
	Path();
	Path(int x, int y);

	int genPath(vector<vector<bool>> nMap);
	bool expand( aStarNode n, int n_index);
	coord move(coord cur); //possibly redundant at this point.
	void setStart(coord s);
	void setGoal(coord g);
	void setNodemap(vector<vector<bool>> nMap);
	int numPaths(coord c);
	queue<coord> getPath();
	coord getNext();
	bool isEmpty();
	void pop();
};

aStarNode makeAstar(coord nSelf, coord nParent, int Nlength, int nTogo, int parent_i);
coord gC( int x, int y );
int intDist(coord a, int x, int y); //for the A* algorithm

#endif