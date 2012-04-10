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

class Path
{
private:
	vector<vector<bool>> Nodemap;
	coord start;
	coord goal;
	stack<coord> p;
	coord mapsize;
	queue<coord> fPath;
public:
	Path();
	Path(int x, int y);

	int genPath(vector<vector<bool>> nMap);
	coord move(coord cur); //possibly redundant at this point.
	void setStart(coord s);
	void setGoal(coord g);
	int numPaths(coord c);
	queue<coord> getPath();
	coord getNext();
	bool isEmpty();
	void pop();
};


#endif