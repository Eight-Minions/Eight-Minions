#include "creep.h"


creep::creep(){
}
creep::creep(int t, int l, int set_x, int set_y){
	type = t;
	level = l;
	health = 0;
	speed = 0;
	this->setX(set_x);  // Should probably have a generic starting point for each side 
	this->setY(set_y);
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
void creep::move(){
	// location next = NULL;
	// Calculate Path;
	// Move one step forward or two if it is fast
}

void creep::calculatePath(){
	// Update that queue
}

void creep::displayCreep(SDL_Surface *screen)
{
	this->r->x = this->getX();
	this->r->y = this->getY();
	SDL_BlitSurface(this->img, NULL, screen, r);
}