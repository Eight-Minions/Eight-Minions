#include "UpdMess.h"
UpdMess::UpdMess(){
}
UpdMess::UpdMess(int p, int t, ...){
	int var;
	char buff[8];
	va_list v1;	
	va_start(v1, t);

	messText = "";
	messText += (t + '0');
	messText += (p + '0');
 
	if(t == TOWERATTACK){ 
		for(int i = 0; i < 3; i++){
			var = va_arg(v1, int);
			if(i == 0 || i == 1){
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--){
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if( i == 2){
				if(var < 10)
					messText += '0';
				messText += itoa(var,buff,10);
			}
			else{
					//ERROR
			}
		}
	}
	else if(t == TOWER || t == CREEP){
		for(int i = 0; i < 4; i++){
			var = va_arg(v1, int);
			if(i == 0 || i == 1 || i == 2){
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--){
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if(i == 3){
				if(t == CREEP){
					for(int n = 4 - (int)floor(log10((double)var)); n > 0; n--){
						messText += '0';
					}
					messText += itoa(var,buff,10);
				}
				if(t == TOWER){

					if(var < 10)
						messText += '0';
					messText += itoa(var,buff,10);
				}
			}
			else{
				// ERROR
			}
		}
	}
	else{
		// ERROR
	}
	va_end(v1);
}
UpdMess::UpdMess(string m){
	type = m[0] - '0';
	p = m[1] - '0';
	if(type == CREEP){
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
	}
	else if(type == TOWER){
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10 * (m[14] - '0') + (m[15] - '0');
	}
	else if(type == TOWERATTACK){
		// Tower (ID1) attack Creep (ID2) with attack type (vala)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		vala = 10 * (m[10] - '0') + (m[11] - '0');
	}
}

UpdMess::~UpdMess(){
}
int UpdMess::setMess(string m){
	if(m == "NO MESSAGE"){
		return 0;
	}
	type = m[0] - '0';
	p = m[1] - '0';
	if(type == CREEP){
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
	}
	else if(type == TOWER){
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		vala = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		valb = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		valc = 10 * (m[14] - '0') + (m[15] - '0');
	}
	else if(type == TOWERATTACK){
		// Tower (ID1) attack Creep (ID2) with attack type (vala)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		vala = 10 * (m[10] - '0') + (m[11] - '0');
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