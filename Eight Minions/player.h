#ifndef PLAYER_H
#define PLAYER_H

class player
{
private:
	int pNum;
	int health;
	int money;

	int specialization;

	//TODO:
	//defines for each spec
	//modifications for each spec

public:
	player();

	int getHealth();
	int getMoney();

	void setHealth(int nHealth);
	void setMoney(int nMoney);

	void addHealth(); //adds one to health
	bool takeDamage(); //subtracts one from health, checks if player has no health

	void addMoney(int amt); //adds the amount of money to the players total
	bool spendMoney(int amt); //checks if the player has enough money, then subtracts it

};

#endif