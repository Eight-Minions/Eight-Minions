#ifndef UPDMESS_H
#define UPDMESS_H
#include "resources.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

#define CREEP 0
#define TOWER 1
#define TOWERATTACK 2

#define MAX_NUM_VAL 5

class UpdMess{
public:
	UpdMess();
	UpdMess(int player, int type, ...);
	UpdMess(string m);
	~UpdMess();
	int setMess(string m);
	string getMT();

	int getVal(int n);
	int getId1();
	int getId2();
	int getType();

	int getPlayer();
private:
	string messText;
	vector<int> val;
	int p;
	int type;
	int id1;
	int id2;
};

#endif