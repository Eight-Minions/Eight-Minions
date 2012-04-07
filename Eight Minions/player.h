
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

	void addMoney(int amt);
	bool spendMoney(int amt);

};