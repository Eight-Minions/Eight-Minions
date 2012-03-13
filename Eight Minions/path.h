#ifndef PATH_H
#define PATH_H
#include <vector>

using std::vector;

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
	vector<coord> p;
public:
	int genPath();
	void setNodeMap();
};


#endif