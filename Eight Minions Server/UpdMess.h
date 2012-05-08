#ifndef UPDMESS_H
#define UPDMESS_H
#include "resources.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class UpdMess{
public:
	UpdMess();
	UpdMess(int player, int type, ...);
	UpdMess(string m);
	~UpdMess();
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