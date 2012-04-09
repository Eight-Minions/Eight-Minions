
class player
{
private:
	int health;
	int money;

public:
	player();

	int getHealth();
	int getMoney();

	void setHealth();
	void setMoney();

	void addHealth(); //adds one to health
	bool takeDamage(); //subtracts one from health, checks if player has no health

	void addMoney(int amt); //adds the amount of money to the players total
	bool spendMoney(int amt); //checks if the player has enough money, then subtracts it

};