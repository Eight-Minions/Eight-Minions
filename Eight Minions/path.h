#ifndef PATH_H
#define PATH_H
#include <vector>
#include <stack>
#include <queue>
#include <math.h>

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

	int genPath();
	void setNodeMap();
	coord move(coord cur);
	void setStart(int x, int y);
	void setGoal(int x, int y);
	int numPaths(coord c);
};


#endif