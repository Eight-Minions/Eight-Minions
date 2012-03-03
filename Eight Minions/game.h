#include "resources.h"

class location
{
private:
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

public:

};

