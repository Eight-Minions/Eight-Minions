#ifndef PATH_H
#define PATH_H
#include <vector>
#include <stack>
#include <queue>

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
public:
	Path(int x, int y);

	int genPath();
	void setNodeMap();
	int move(int dx, int dy);
	void setStart(int x, int y);
	void setGoal(int x, int y);
	int numPaths(coord c);
};


#endif