#include "creep.h"


creep::creep(){
}

creep::creep(int t, int l, int set_x, int set_y){
	type = t;
	level = l;
	health = 0;
	speed = 0;
	prevPos.x = set_x;
	prevPos.y = set_y;
	this->setX(set_x * 16 + BOARD_X_OFFSET);  // Should probably have a generic starting point for each side 
	this->setY(set_y * 16 + BOARD_Y_OFFSET);
	// TL: just some more ideas
	this->r = new SDL_Rect;
	if(type == TANK){
		health = 50;
		speed = 1;
		armor = 3;
		this->img = IMG_Load("tank.png");
	}
	else if(type == FAST){
		health = 30;
		speed = 3;
		armor = 0;
		this->img = IMG_Load("fast.png");
	}
	else if(type == SWARM)
	{
		health = 25;
		speed = 2;
		armor = 0;
		this->img = IMG_Load("swarm.png");
	}else if(type == TITAN)
	{
		health = 60;
		speed = 1;
		armor = 5;
		this->img = IMG_Load("titan.png");
	}else if(type == NORM)
	{
		health = 35;
		speed = 2;
		armor = 1;
		this->img = IMG_Load("norm.png");
	}
	health = health * level; //maybe a little different like (health = health * (1 + (.5 * level)))
	//also, i want to do similar modifications for each attribute.
	if(img == NULL)
	{
		cout << "creep image failed to load\n";
	}
	// Calculate path.
	
}
creep::~creep(){
	// Kill off that Queue?
	// sounds about right
}

int creep::damage(int d){
	this->health = this->health - d;
	if(this->health <= 0){
		// Remove from the list of creeps
		// Kill this object
		return 0;
	}
	return this->health;
}
bool creep::move(){
	coord next = p.getNext();
	double difX = getXd() - (next.x * 16) + BOARD_X_OFFSET;
	double difY = getYd() - (next.y * 16) + BOARD_Y_OFFSET;

	Xdir = next.x - prevPos.x;
	Ydir = next.y - prevPos.y;

	setX(getXd() + (speed * Xdir * CLOCK_CAP));
	setY(getYd() + (speed * Ydir * CLOCK_CAP));

	if(getXd() > 580)
	{
		cout << "debug start\n";
	}
	if(Xdir != 0 && getXd() * Xdir >= (next.x * 16 * Xdir) + BOARD_X_OFFSET)
	{

		double extra = (getXd() * Xdir) - ((next.x * 16 * Xdir) + BOARD_X_OFFSET);
		prevPos = next;
		p.pop();
		if(p.isEmpty())
		{
			//creep got to enemy base, success.
			cout << "creep got to base\n";
			return true;
		}
		next = p.getNext();

		Xdir = next.x - prevPos.x;
		Ydir = next.y - prevPos.y;

		setX(prevPos.x * 16 + BOARD_X_OFFSET);
		setX(getXd() + (Xdir * extra));
		setY(getYd() + (Ydir * extra));

	}

	if(Ydir != 0 && getYd() * Ydir >= (next.y * 16 * Ydir) + BOARD_Y_OFFSET)
	{
		if(p.isEmpty())
		{
			//creep got to enemy base, success.
			cout << "creep got to base\n";
		}
		double extra = (getYd() * Ydir) - ((next.y * 16 * Ydir) + BOARD_Y_OFFSET);
		prevPos = next;
		p.pop();
		next = p.getNext();

		Xdir = next.x - prevPos.x;
		Ydir = next.y - prevPos.y;

		setY(prevPos.y * 16 + BOARD_Y_OFFSET);
		setX(getXd() + (Xdir * extra));
		setY(getYd() + (Ydir * extra));

	}

	return false;
}



void creep::displayCreep(SDL_Surface *screen)
{
	//blah
	this->r->x = this->getX();
	this->r->y = this->getY();
	SDL_BlitSurface(this->img, NULL, screen, r);
}
