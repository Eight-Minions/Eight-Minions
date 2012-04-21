#include "UpdMess.h"
UpdMess::UpdMess()
{
}
UpdMess::UpdMess(int p, int t, ...)
{

	/*
		Creep:					UpdMess(Player[1], NEWCREEP, CreepID[4], X[4], Y[4], Health[5], Type[2], Level[3]);	// For creep creation and upgrades
		Creep:					UpdMess(Player[1], CREEP, CreepID[4], X[4], Y[4], Health[5], Direction[1]);						// For position updates
		Player:					UpdMess(Player[1], PLAYERUPDATE, Health[3], Money[8]);
		Add Type to Base:		UpdMess(Player[1], BASE, ADDTYPE, addType[2]);
		Upgrade Base:			UpdMess(Player[1], BASE, UPGRADE);
		Tower Creation:			UpdMess(Player[1], TOWER, TOWERCREATION[2], TowerID[4], X[2], Y[2], TowerType[2]);
		Tower Attack:			UpdMess(Player[1], TOWER, TOWERATTACK[2], AttackerX[2], AttackerY[2], AttackedID[4], AttackType[2]);
		Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE[2], TowerX[2], Tower[Y]);
		Tower Upgrade:			UpdMess(Player[1], TOWER, TOWERUPGRADE[2], TowerID[4]);
		Tower ChangeType:		UpdMess(Player[1], TOWER, TOWERCHANGE[2], TowerID[4], newType[2]);	
		Tower Toggle Pause:		UpdMess(Player[1], TOWER, TOWERTOGGLE[2], TowerID[4], newValue);
		Tower Delete			UpdMess(Player[1], TOWER, TOWERDELETE, TowerID[4]);
		Mine Placement:			UpdMess(Player[1], TOWER, MINEPLACE[2], TowerX[2], Tower[Y]);
		Obstruction Placement:	UpdMess(Player[1], TOWER, OBSTACLEPLACE[2], TowerX[2], Tower[Y]);
		Game Over:				UpdMess(Player[1], GAMEOVER, Winner[1]);
	*/	
	int var;
	char buff[8];
	va_list v1;	
	va_start(v1, t);

	messText = "";
	messText += (p + '0');
	this->p = p;
	messText += (t + '0');
	this->type = t;

	if(t == BASE)
	{
		var = va_arg(v1, int);
		if(var == 0)
			messText += "00";
		else
		{
			if(var < 10)
				messText += '0';
			messText += itoa(var,buff,10);
		}
		if(var == ADDTYPE)
		{
			var = va_arg(v1, int);
			if(var == 0)
				messText += "00";
			else
			{
				if(var < 10)
					messText += '0';
				messText += itoa(var,buff,10);
			}
		}
		else if(var == UPGRADE)
		{
			// Do nothing for now.
		}
		else
		{
		}
	}
	if(t == TOWER)
	{ 
		var = va_arg(v1, int);
		if(var == 0)
			messText += "00";
		else
		{
			if(var < 10)
				messText += '0';
			messText += itoa(var,buff,10);
		}
		if(var == TOWERATTACK)
		{
			for(int i = 0; i < 4; i++)
			{
				var = va_arg(v1, int);
				// i = 0 AttackerX[2]
				// i = 1 AttackerY[2]
				// i = 3 AttackType
				if( i == 0 || i == 1 || i == 3)
				{
					if(var == 0)
						messText += "00";
					else
					{
						if(var < 10)
							messText += '0';
						messText += itoa(var,buff,10);
					}
				}
				// i = 2 AttackedID[4]
				else if(i == 2)
				{
					if(var == 0)
						messText += "0000";
					else
					{
						for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
						messText += itoa(var,buff,10);
					}
				}
				else
				{
						//
				}
			}
		}
		else if(var == TOWERCREATION)
		{
			for (int i = 0; i < 4; i++)
			{
				var = va_arg(v1, int);
				// TowerID
				if(i == 0){
					if(var == 0)
						messText += "0000";
					else
					{
						for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
						messText += itoa(var,buff,10);
					}
				}
				// i = 1 X
				// i = 2 Y
				// i = 3 TowerType
				else{
					if(var == 0)
						messText += "00";
					else
					{
						if(var < 10)
							messText += '0';
						messText += itoa(var,buff,10);
					}
				}
			}
		}
		//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE, TowerX[2], Tower[Y]);
		else if(var == TOWERPLACE || var == MINEPLACE || var == OBSTACLEPLACE)
		{
			for(int i = 0; i < 2; i++)
			{
				var = va_arg(v1, int);
				// X and Y (len 2)
				if(i == 0 || i == i)
				{
					if(var == 0)
						messText += "00";
					else
					{
						if(var < 10)
							messText += '0';
						messText += itoa(var,buff,10);
					}
				}
			}
		}	
		//Tower Upgrade:			UpdMess(Player[1], TOWER, TOWERUPGRADE, TowerID[4]);
		else if(var == TOWERUPGRADE)
		{
			for(int i = 0; i < 1; i++)  // Not necessary, I did it for expansion...
			{
				var = va_arg(v1, int);
				if(i == 0)
				{
					if(var == 0)
						messText += "0000";
					else
					{
						for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
						messText += itoa(var,buff,10);
					}
				}
			}
		}
		//Tower ChangeType:		UpdMess(Player[1], TOWER, TOWERCHANGE, TowerID[4], newType[2]);
		else if(var == TOWERCHANGE)
		{
			for(int i = 0; i < 2; i++)
			{
				var = va_arg(v1, int);
				if(i == 0)
				{
					if(var == 0)
						messText += "0000";
					else
					{
						for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
						messText += itoa(var,buff,10);
					}
				}
				else if(i == 1)
				{
					if(var == 0)
						messText += "00";
					else
					{
						if(var < 10)
							messText += '0';
						messText += itoa(var,buff,10);
					}
				}
			}
		}
		//Tower Toggle Pause:		UpdMess(Player[1], TOWER, TOWERTOGGLE, TowerID[4], newValue);
		else if(var == TOWERTOGGLE)
		{
			for(int i = 0; i < 2; i++)
			{
				var = va_arg(v1, int);
				if(i == 0)
				{
					if(var == 0)
						messText += "0000";
					else
					{
						for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
						messText += itoa(var,buff,10);
					}
				}
				else if(i == 1)
				{
					if(var == 0)
						messText += "0";
					else
					{
						messText += itoa(var,buff,10);
					}
				}
			}
		}
		else if(var == TOWERDELETE)
		{
			var = va_arg(v1, int);
			if(var == 0)
				messText += "0000";
			else
			{
				for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
				{
					messText += '0';
				}
				messText += itoa(var,buff,10);
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
			// i = 1 CreepID
			// i = 2 X
			// i = 3 Y
			if(i == 0 || i == 1 || i == 2)
			{
				if(var == 0)
					messText += "0000";
				else
				{
					for(int n = 3 - (int)floor(log10((double)var)); n > 0; n--)
					{
						messText += '0';
					}
					messText += itoa(var,buff,10);
				}
			
			}
			// Health
			else if(i == 3)
			{
				if(var == 0)
					messText += "00000";
				else
				{
					for(int n = 4 - (int)floor(log10((double)var)); n > 0; n--)
					{
						messText += '0';
					}
					messText += itoa(var,buff,10);
				}
			}
			// Creep Type
			else if(i == 4)
			{
				if(var == 0)
					messText += "00";
				{
					if(var < 10)
						messText += '0';
					messText += itoa(var,buff,10);
				}
			}
			// Creep Level
			else if(i == 5)
			{
				if(var == 0)
					messText += "000";
				else
				{
					for(int n = 2 - (int)floor(log10((double)var)); n > 0; n--)
						{
							messText += '0';
						}
					messText += itoa(var,buff,10);
				}
			}
			else
			{
				// ERROR
			}
		}
	}
	else if(t == PLAYERUPDATE)
	{
		for (int i = 0; i < 2; i++)
		{
			var = va_arg(v1, int);
			// Health
			if(i == 0)
			{
				if(var == 0)
					messText += "000";
				else
				{
					for(int n = 2 - (int)floor(log10((double)var)); n > 0; n--)
					{
						messText += '0';
					}
					messText += itoa(var,buff,10);
				}
			}
			// Money
			else if(i == 1)
			{
				if(var == 0)
					messText += "00000000";
				else
				{
					for(int n = 7 - (int)floor(log10((double)var)); n > 0; n--)
					{
						messText += '0';
					}
					messText += itoa(var,buff,10);
				}
			}
			else
			{
				// Space to expand
			}
		}
	}
	else if(t == GAMEOVER)
	{
		var = va_arg(v1, int);
		messText += itoa(var,buff,10);
	}
	else{
		// ERROR
	}
	va_end(v1);
	if(messText.length() == 21)
		cout << "weird...\n";
}
UpdMess::UpdMess(string m)
{
	p = m[0] - '0';
	type = m[1] - '0';
	if(type == CREEP || type == NEWCREEP)
	{
		if (type == NEWCREEP)
		{
			val.resize(5);
			// TYPE
			val[3] = 10 * (m[19] - '0') + (m[20] - '0');
			// LEVEL
			val[4] = 100 * (m[21] - '0') + 10 * (m[22] - '0') + (m[23] - '0');
		}
		else
		{
			val.resize(3);
		}
		// ID
		id1 = 1000 * (m[2] - '0') + 100 * (m[3] - '0') + 10 * (m[4] - '0') + (m[5] - '0');
		// X
		val[0] = 1000 * (m[6] - '0') + 100 * (m[7] - '0') + 10 * (m[8] - '0') + (m[9] - '0');
		// Y
		val[1] = 1000 * (m[10] - '0') + 100 * (m[11] - '0') + 10 * (m[12] - '0') + (m[13] - '0');
		// HEALTH
		val[2] = 10000 * (m[14] - '0') + 1000 * (m[15] - '0') + 100 * (m[16] - '0') + 10 * (m[17] - '0') + (m[18] - '0');
		//UpdMess(Player[1], CREEP, CreepID[4], X[4], Y[4], Health[5], Type[2], Level[3]);
	}
	else if(type == BASE)
	{	
		val.resize(1);
		val[0] = 10 * (m[2] - '0') + (m[3] - '0');
		if(val[0] == ADDTYPE)
		{
			val.resize(2);
			val[1] = 10 * (m[4] - '0') + (m[5] - '0'); 
		}
		else if(val[0] == UPGRADE)
		{
			// Do nothing
		}
		else
		{
			//break
		}
	}
	else if(type == TOWER)
	{
		val.resize(1);
		val[0] = 10 * (m[2] - '0') + (m[3] - '0');
		if(val[0] == TOWERCREATION)
		{
			val.resize(4);
			// ID
			id1 = 1000 * (m[4] - '0') + 100 * (m[5] - '0') + 10 * (m[6] - '0') + (m[7] - '0');
			// X
			val[1] = 10 * (m[8] - '0') + (m[9] - '0');
			// Y
			val[2] = 10 * (m[10] - '0') + (m[11] - '0');
			// TYPE
			val[3] = 10 * (m[12] - '0') + (m[13] - '0');
		}
		else if(val[0] == TOWERATTACK)
		{
			val.resize(4);
			// Attacker's X
			val[1] = 10 * (m[4] - '0') + (m[5] - '0');
			// Attacker's Y
			val[2] = 10 * (m[6] - '0') + (m[7] - '0');
			// Who got attacked
			id1 = 1000 * (m[8] - '0') + 100 * (m[9] - '0') + 10 * (m[10] - '0') + (m[11] - '0');
			// ATTACK TYPE
			val[3] = 10 * (m[12] - '0') + (m[13] - '0');
		}
		//Tower Placement:		UpdMess(Player[1], TOWER, TOWERPLACE, TowerX[2], Tower[Y]);
		else if(val[0] == TOWERPLACE || val[0] == MINEPLACE || val[0] == OBSTACLEPLACE)
		{
			val.resize(3);
			// Placement X
			val[1] = 10 * (m[4] - '0') + (m[5] - '0');
			// Placement Y
			val[2] = 10 * (m[6] - '0') + (m[7] - '0'); 
		}
		//Tower Upgrade:			UpdMess(Player[1], TOWER, TOWERUPGRADE, TowerID[4]);
		else if(val[0] == TOWERUPGRADE)
		{
			id1 = 1000 * (m[4] - '0') + 100 * (m[5] - '0') + 10 * (m[6] - '0') + (m[7] - '0');
		}
		//Tower ChangeType:		UpdMess(Player[1], TOWER, TOWERCHANGE, TowerID[4], newType[2]);	
		else if(val[0] == TOWERCHANGE)
		{
			val.resize(2);
			id1 = 1000 * (m[4] - '0') + 100 * (m[5] - '0') + 10 * (m[6] - '0') + (m[7] - '0');
			val[1] = 10 * (m[8] - '0') + (m[9] - '0');
		}
		//Tower Toggle Pause:		UpdMess(Player[1], TOWER, TOWERTOGGLE, TowerID[4], newValue);
		else if(val[0] == TOWERTOGGLE)
		{
			val.resize(2);
			id1 = 1000 * (m[4] - '0') + 100 * (m[5] - '0') + 10 * (m[6] - '0') + (m[7] - '0');
			val[1] = (m[8] - '0');
		}
		else if(val[0] == TOWERDELETE)
		{
			id1 = 1000 * (m[4] - '0') + 100 * (m[5] - '0') + 10 * (m[6] - '0') + (m[7] - '0');
		}
		else
			m.append("ERROR Undefined Type");
	}
	else if(type == PLAYERUPDATE)
	{
		val.resize(2);
		val[0] = 100 * (m[2] - '0') + 10 * (m[3] - '0') + (m[4] - '0');
		val[1] = 10000000 * (m[5] - '0') + 1000000 * (m[6] - '0') + 100000 * (m[7] - '0') + 10000 * (m[8] - '0') + 1000 * (m[9] - '0') + 100 * (m[10] - '0') + 10 * (m[11] - '0') +  (m[12] - '0');	
	}
	else if(type == GAMEOVER)
	{
		val.resize(1);
		val[0] = (m[2] - '0');
	}
	else{
		m.append("ERROR Undefined Type");
	}
}

UpdMess::~UpdMess()
{
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