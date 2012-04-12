#include "creep.h"

creep::creep()
{
}
creep::creep(int t, int p, int l, int set_x, int set_y)
{
	alive = true;
	type = t;
	level = l;
	animIndex = 0;
	animTiming = 5;
	animCount = 0;
	prevPos.x = set_x;
	prevPos.y = set_y;
	this->setX(set_x * GRID_SIZE + BOARD_X_OFFSET);  // Should probably have a generic starting point for each side 
	this->setY(set_y * GRID_SIZE + BOARD_Y_OFFSET);
	this->r = new SDL_Rect;
	if(type == TANK){
		// Health Armor Speed Reward Price
		health =	tankCreepArr[level-1][0];
		armor =		tankCreepArr[level-1][1];
		speed =		tankCreepArr[level-1][2];
		reward =	tankCreepArr[level-1][3];
		price =		tankCreepArr[level-1][4];
		this->img = IMG_Load("tank.png");
	}
	else if(type == FAST){
		health =	fastCreepArr[level-1][0];
		armor =		fastCreepArr[level-1][1];
		speed =		fastCreepArr[level-1][2];
		reward =	fastCreepArr[level-1][3];
		price =		fastCreepArr[level-1][4];
		this->img = IMG_Load("fast.png");
	}
	else if(type == SWARM)
	{
		health =	swarmCreepArr[level-1][0];
		armor =		swarmCreepArr[level-1][1];
		speed =		swarmCreepArr[level-1][2];
		reward =	swarmCreepArr[level-1][3];
		price =		swarmCreepArr[level-1][4];
		this->img = IMG_Load("swarm.png");
	}
	else if(type == TITAN)
	{

		health =	titanCreepArr[level-1][0];
		armor =		titanCreepArr[level-1][1];
		speed =		titanCreepArr[level-1][2];
		reward =	titanCreepArr[level-1][3];
		price =		titanCreepArr[level-1][4];
		this->img = IMG_Load("titan.png");
	}
	else if(type == NORM)
	{
		health =	normCreepArr[level-1][0];
		armor =		normCreepArr[level-0][1];
		speed =		normCreepArr[level-0][2];
		reward =	normCreepArr[level-0][3];
		price =		normCreepArr[level-0][4];
		this->img = IMG_Load("norm.png");
	}
	else
	{
		health = 0;
		armor = 0;
		speed = 0;
		reward = 0;
		price = 0;
		this->img = NULL;
	}
	if(img == NULL)
	{
		cout << "creep image failed to load\n";
	}
}
/*
creep::creep(int t, int p, int l, int set_x, int set_y)
{
	alive = true;
	type = t;
	level = l;
	player = p;
	health = 0;
	speed = 0;
	animIndex = 0;
	animTiming = 5;
	animCount = 0;
	prevPos.x = set_x;
	prevPos.y = set_y;
	this->setX(set_x * GRID_SIZE + BOARD_X_OFFSET);  // Should probably have a generic starting point for each side 
	this->setY(set_y * GRID_SIZE + BOARD_Y_OFFSET);
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
}
*/

creep::~creep()
{
	delete img;
	delete r;
}

int creep::damage(int d)
{
	this->health = this->health - d;
	if(health <= 0)
	{
		alive = false;
		return 0;
	}
	return health;
}

bool creep::move()
{
	//moves creep towards its goal along its generated path by one unit of its speed
	//returns true when creep reaches goal, false otherwise
	if(p.isEmpty())
	{
		cout << "creep has reached its goal, please kill it off\n";
		return true;
	}
	coord next = p.getNext();

	Xdir = next.x - prevPos.x;
	Ydir = next.y - prevPos.y;

	setX(getXd() + (speed * Xdir * CLOCK_CAP));
	setY(getYd() + (speed * Ydir * CLOCK_CAP));

	if(Xdir != 0 && getXd() * Xdir >= (next.x * GRID_SIZE * Xdir) + (BOARD_X_OFFSET * Xdir))
	{

		double extra = (getXd() * Xdir) - ((next.x * GRID_SIZE * Xdir) + (BOARD_X_OFFSET * Xdir));
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

		setX(prevPos.x * GRID_SIZE + BOARD_X_OFFSET);
		setX(getXd() + (Xdir * extra));
		setY(getYd() + (Ydir * extra));

	}

	if(Ydir != 0 && getYd() * Ydir >= (next.y * GRID_SIZE * Ydir) + (BOARD_Y_OFFSET * Ydir))
	{
		if(p.isEmpty())
		{
			//creep got to enemy base, success.
			cout << "creep got to base\n";
			return true;
		}
		double extra = (getYd() * Ydir) - ((next.y * GRID_SIZE * Ydir) + (BOARD_Y_OFFSET * Ydir));
		prevPos = next;
		p.pop();
		next = p.getNext();

		Xdir = next.x - prevPos.x;
		Ydir = next.y - prevPos.y;

		setY(prevPos.y * GRID_SIZE + BOARD_Y_OFFSET);
		setX(getXd() + (Xdir * extra));
		setY(getYd() + (Ydir * extra));

	}

	return false;
}

void creep::displayCreep(SDL_Surface *screen, SDL_Surface *images[4])
{
	updateAnim();
	this->r->x = this->getX();
	this->r->y = this->getY();
	SDL_BlitSurface(this->img, NULL, screen, r);
}
void creep::updateAnim()
{
	
}
void creep::recalcPath( vector<vector<bool>> nMap )
{
	p.setStart(p.getNext());
	p.genPath(nMap);
}

int creep::getHealth()
{
	return health;
}
int creep::setHealth(int newHealth)
{
	health = newHealth;
	return health;
}
void creep::setPlayer( int p )
{
	player = p;
}
int creep::getPlayer()
{
	return player;
}
int creep::getType()
{
	return type;
}
int creep::getLevel()
{
	return level;
}
int creep::getReward()
{
	return reward;
}
int creep::getArmor()
{
	return armor;
}
bool creep::isAlive()
{
	return alive;
}
int creep::getPrice()
{
	return price;
}