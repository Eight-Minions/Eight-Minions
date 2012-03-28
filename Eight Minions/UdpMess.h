#ifndef UPDMESS_H
#define UPDMESS_H
#include <string>
#include <cmath>

using std::string;

class UpdMess
{
private:
	string messText;
	//different message types have different formats, we need to define them.
	//J: what types of messages do we need to send?
	int type;
	int vala;
	int valb;
	int valc;
	int p;
	int id1;
	int id2;

public:
	UpdMess();
	UpdMess(int t, int pl, int id, int cx, int cy, int ch);
	UpdMess(int t, int pl, int ida, int idb, int atype);
	UpdMess(int t, int pl, int id, int cx, int cy, int Ttype);
	UpdMess(string m);

	int setMess(string m);
	string getMT();
	int getType();
	int getVala();
	int getValb();
	int getValc();
	int getId1();
	int getId2();
	int getPlayer();

};









#endif