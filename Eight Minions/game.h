#include "resources.h"

class location
{
private:
	location();
	int x;
	int y;
public:
	int getX();
	int getY();
	void setX(int new_x);
	void setY(int new_y);
};


class object : public location 
{
private:
	/*
	object();
	~object();
	double health;
public:
	double getHealth();
	void setHealth(double new_health);
	*/
};

