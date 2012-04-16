#include "player.h"


player::player()
{
	this->health = 30;
	this->money = 20;
}

int player::getHealth()
{
	return health;
}

int player::getMoney()
{
	return money;
}

void player::setHealth(int nHealth)
{
	health = nHealth;
}

void player::setMoney(int nMoney)
{
	money = nMoney;
}

void player::addHealth()
{
	health++;
}

bool player::takeDamage()
{
	health -= 1;
	if(health <= 0)
		return true;
	else
		return false;
}

void player::addMoney( int amt )
{
	money += amt;
}

bool player::spendMoney( int amt )
{
	if(amt > money)
		return false;
	else
	{
		money -= amt;
		return true;
	}
}

void player::setPnum( int nPnum )
{
	this->pNum = nPnum;
}

int player::getPnum()
{
	return pNum;
}


