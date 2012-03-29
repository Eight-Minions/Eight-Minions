#ifndef UPDMESS_H
#define UPDMESS_H
#include "resources.h"
#include <string>

using std::string;

#define CREEP 0
#define TOWER 1
#define TOWERATTACK 2

class UpdMess{
public:
	UpdMess();
	UpdMess(int player, int type, ...);
	UpdMess(string m);
	~UpdMess();
	int setMess(string m);
	string getMT();
	int getType();
	int getVala();
	int getValb();
	int getValc();
	int getId1();
	int getId2();
	int getPlayer();
private:
	string messText;
	int type;
	int vala;
	int valb;
	int valc;
	int p;
	int id1;
	int id2;
};

#endif