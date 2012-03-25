#include "UdpMess.h"

UpdMess::UpdMess()
{
	messText = "";
	vala = -1;
	id1 = -1;
	type = -1;
}

UpdMess::UpdMess( int t, int pl, int id, int cx, int cy, int ch )
{	
	char buff[8];
	messText = "";
	messText += (t + '0');
	messText += (pl + '0');

	for(int n = 3 - floor(log10((double)id)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(id,buff,10);
	for(int n = 3 - floor(log10((double)cx)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(cx,buff,10);
	for(int n = 3 - floor(log10((double)cy)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(cy,buff,10);
	for(int n = 4 - floor(log10((double)ch)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(ch,buff,10);
}


UpdMess::UpdMess( int t, int pl, int ida, int idb, int atype )
{
	char buff[8];
	messText = "";
	messText += (t + '0');
	messText += (pl + '0');
	for(int n = 3 - floor(log10((double)ida)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(ida,buff,10);
	for(int n = 3 - floor(log10((double)idb)); n > 0; n--){
		messText += '0';
	}
	messText += itoa(idb,buff,10);

	if(atype < 10)
		messText += '0';
	messText += itoa(atype,buff,10);
}

UpdMess::UpdMess( string m )
{
	type = m[0] - '0';
	p = m[1] - '0';
	switch(type)
	{
	case 1:
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
		break;
	case 2:
		// Tower (ID1) attack Creep (ID2) with attack type (vala)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		vala = 10 * (m[10] - '0') + (m[11] - '0');
	}



}

int UpdMess::setMess( string m )
{
	if(m == "NO MESSAGE")
	{
		return 0;
	}
	type = m[0] - '0';
	p = m[1] - '0';
	switch(type)
	{
	case 1:
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
		break;
	case 2:
		// Tower (ID1) attack Creep (ID2) with attack type (vala)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		vala = 10 * (m[10] - '0') + (m[11] - '0');
		break;
	}
	return 1;
}

string UpdMess::getMT()
{
	return messText;
}

int UpdMess::getVala()
{
	return vala;
}

int UpdMess::getValb()
{
	return valb;
}

int UpdMess::getValc()
{
	return valc;
}

int UpdMess::getId1()
{
	return id1;
}

int UpdMess::getId2()
{
	return id2;
}

int UpdMess::getPlayer()
{
	return p;
}

int UpdMess::getType()
{
	return type;
}