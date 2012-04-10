#include "UpdMess.h"
UpdMess::UpdMess()
{
}
UpdMess::UpdMess(int p, int t, ...)
{

	/*
		Creep:			UpdMess(Player[1], CREEP, CreepID[4], X[4], Y[4], Health[5], Type[2], Level[3]);	// For creep creation and upgrades
		Creep:			UpdMess(Player[1], CREEP, CreepID[4], X[4], Y[4], Health[5]);						// For position updates
		Tower:			UpdMess(Player[1], TOWER, TowerID[4], X[2], Y[2], TowerType[2]);
		Tower Attack:	UpdMess(Player[1], TOWERATTACK, AttackerID[4], AttackedID[4], AttackType[2]);
		Player:			UpdMess(Player[1], PLAYERUPDATE, Health[3], Money[8]);
	*/
	int var;
	char buff[8];
	va_list v1;	
	va_start(v1, t);

	messText = "";
	messText += (p + '0');
	messText += (t + '0');
 
	if(t == TOWERATTACK)
	{ 
		for(int i = 0; i < 3; i++)
		{
			var = va_arg(v1, int);
			if(i == 0 || i == 1)
			{
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if( i == 2)
			{
				if(var < 10)
					messText += '0';
				messText += itoa(var,buff,10);
			}
			else
			{
					//ERROR
			}
		}
	}
	else if(t == CREEP || t == NEWCREEP)
	{
		for(int i = 0; i < 6; i++)
		{
			var = va_arg(v1, int);
			if(i >= 4 && t == CREEP)
				break; // The update type of a Creep is only 4 vars.
			if(i == 0 || i == 1 || i == 2)
			{
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if(i == 3)
			{
				for(int n = 4 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if(i == 4)
			{
				if(var < 10)
					messText += '0';
				messText += itoa(var,buff,10);
			}
			else if(i == 5)
			{
				for(int n = 2 - (int)floor(log10((double)var)); n > 0; n--)
					{
						messText += '0';
					}
				messText += itoa(var,buff,10);
			}
			else
			{
				// ERROR
			}
		}
	}
	else if(t == TOWER){
		for (int i = 0; i < 4; i++)
		{
			var = va_arg(v1, int);
			if(i == 0){
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else{
				if(var < 10)
					messText += '0';
				messText += itoa(var,buff,10);
			}
		}
	}
	else if(t == PLAYERUPDATE)
	{
		for (int i = 0; i < 2; i++)
		{
			var = va_arg(v1, int);
			if(i == 0)
			{
				for(int n = 2 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else if(i == 1)
			{
				for(int n = 7 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
			}
			else
			{
				// Space to expand
			}
		}
	}
	else{
		// ERROR
	}
	va_end(v1);
}
UpdMess::UpdMess(string m){
	/*
	for(int i = 0; i < MAX_NUM_VAL; i++) //Couldnt we just do a val.resize(MAX_NUM_VAL) here?
		val.push_back(0);
	*/
	//val.resize(MAX_NUM_VAL);

	p = m[0] - '0';
	type = m[1] - '0';

	if(type == CREEP || type == NEWCREEP)
	{
		val.resize(3);
		// ID
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		// X
		val[0] = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		// Y
		val[1] = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		// HEALTH
		val[2] = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
		if (type == NEWCREEP){
			val.resize(5);
			// TYPE
			val[3] = 10 * (m[19] - '0') + (m[20] - '0');
			// LEVEL
			val[4] = 100 * (m[21] - '0') + 10 * (m[22] - '0') + (m[23] - '0');
		}
	}
	else if(type == TOWER)
	{
		val.resize(3);
		// ID
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		// X
		val[0] = 10 * (m[6] - '0') + (m[7] - '0');
		// Y
		val[1] = 10 * (m[8] - '0') + (m[9] - '0');
		// TYPE
		val[2] = 10 * (m[10] - '0') + (m[11] - '0');
	}
	else if(type == TOWERATTACK)
	{
		val.resize(1);
		// ID1
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		// ID2
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		// ATTACK TYPE
		val[0] = 10 * (m[10] - '0') + (m[11] - '0');
	}
	//	Health[3], Money[8]);
	else if(type == PLAYERUPDATE){
		val.resize(2);
		val[0] = 100 * (m[2] - '0') + 10 * (m[3] - '0') + (m[4] - '0');
		val[1] = 10000000 * (m[5] - '0') + 1000000 * (m[6] - '0') + 100000 * (m[7] - '0') + 10000 * (m[8] - '0') + 1000 * (m[9] - '0') + 100 * (m[10] - '0') + 10 * (m[11] - '0') +  (m[12] - '0');	
	}
	else{
		m.append("ERROR Undefined Type");
	}
}

UpdMess::~UpdMess()
{
}
int UpdMess::setMess(string m)
{
	if(m == "NO MESSAGE")
	{
		return 0;
	}
	type = m[0] - '0';
	p = m[1] - '0';
	if(type == CREEP)
	{
		val.resize(3);
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		val[0] = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		val[1] = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		val[2] = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
	}
	else if(type == TOWER)
	{
		val.resize(3);
		// Update Creep Location (x = vala, y = valb) and Health (valc)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		val[0] = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		val[1] = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		val[2] = 10 * (m[14] - '0') + (m[15] - '0');
	}
	else if(type == TOWERATTACK)
	{
		val.resize(1);
		// Tower (ID1) attack Creep (ID2) with attack type (vala)
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		id2 = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		val[0] = 10 * (m[10] - '0') + (m[11] - '0');
	}
	else if(type == PLAYERUPDATE){
		val.resize(2);
		val[0] = 100 * (m[0] - '0') + 10 * (m[1] - '0') + (m[2] - '0');
		val[1] = 10000000 * (m[3] - '0') + 1000000 * (m[4] - '0') + 100000 * (m[5] - '0') + 10000 * (m[6] - '0')
			   + 1000 * (m[7] - '0') + 100 * (m[8] - '0') + 10 * (m[9] - '0') + (m[10] - '0');
	}
	else{
		//
	}
	return 1;
}

string UpdMess::getMT()
{
	return messText;
}
int UpdMess::getVal(int n)
{
	return val[n];
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