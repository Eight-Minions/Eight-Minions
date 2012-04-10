#include "player.h"


player::player()
{
	this->health = 50;
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

bool player::takeDamage(int damage)
{
	health -= damage;
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



