#ifndef UPDMESS_H
#define UPDMESS_H
#include <string>

using std::string;

class UpdMess
{
private:
	string messText;
	//different message types have different formats, we need to define them.
	//J: what types of messages do we need to send?
	int type;
	int val;
	int id;
public:
	UpdMess();
	UpdMess(int t, int v, int i);
	UpdMess(string m);

	string getMT();
	int getType();
	int getVal();
	int getId();

};


#endif