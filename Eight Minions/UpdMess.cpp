#include "UdpMess.h"

UpdMess::UpdMess()
{
	messText = "";
	val = -1;
	id = -1;
	type = -1;
}

UpdMess::UpdMess(int t, int v, int i)
{
	if(type > -1 && type < 10)
		type = t;
	else
		type = -1;
	//need further error checking
	val = v;
	id = i;

}