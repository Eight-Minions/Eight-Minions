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
	animTiming = 4;
	animDelay = 4;
	animCount = 1;
	player = p;
	prevPos.x = set_x;
	prevPos.y = set_y;
	dispDir = 0;
	this->p.setStart(prevPos);
	this->setX(set_x * GRID_SIZE + BOARD_X_OFFSET);  // Should probably have a generic starting point for each side 
	this->setY(set_y * GRID_SIZE + BOARD_Y_OFFSET);
	this->r = new SDL_Rect;
	if(type == TANK)
	{
		// Health Armor Speed Reward Price
		health =	tankCreepArr[level-1][0];
		armor =		tankCreepArr[level-1][1];
		speed =		tankCreepArr[level-1][2];
		reward =	tankCreepArr[level-1][3];
		price =		tankCreepArr[level-1][4];
		animCount = 4;
	}
	else if(type == FATTY)
	{
		// Health Armor Speed Reward Price
		health =	fattyCreepArr[level-1][0];
		armor =		fattyCreepArr[level-1][1];
		speed =		fattyCreepArr[level-1][2];
		reward =	fattyCreepArr[level-1][3];
		price =		fattyCreepArr[level-1][4];
		animCount = 6;
	}
	else if(type == FAST)
	{
		health =	fastCreepArr[level-1][0];
		armor =		fastCreepArr[level-1][1];
		speed =		fastCreepArr[level-1][2];
		reward =	fastCreepArr[level-1][3];
		price =		fastCreepArr[level-1][4];
		animCount = 4;

	}
	else if(type == SWARM)
	{
		health =	swarmCreepArr[level-1][0];
		armor =		swarmCreepArr[level-1][1];
		speed =		swarmCreepArr[level-1][2];
		reward =	swarmCreepArr[level-1][3];
		price =		swarmCreepArr[level-1][4];
		animCount = 4;
	}
	else if(type == TITAN)
	{
		health =	titanCreepArr[level-1][0];
		armor =		titanCreepArr[level-1][1];
		speed =		titanCreepArr[level-1][2];
		reward =	titanCreepArr[level-1][3];
		price =		titanCreepArr[level-1][4];
		animCount = 4;
	}
	else if(type == NORM)
	{
		health =	normCreepArr[level-1][0];
		armor =		normCreepArr[level-1][1];
		speed =		normCreepArr[level-1][2];
		reward =	normCreepArr[level-1][3];
		price =		normCreepArr[level-1][4];
		animCount = 4;
	}
	else
	{
		health = 0;
		armor = 0;
		speed = 0;
		reward = 0;
		price = 0;
	}

	timeOfLastUpdate = SDL_GetTicks() + 500;
}
creep::~creep()
{
	delete r;
}
int creep::getX(){
	return (int)floor(this->x);
}
int creep::getY(){
	return (int)floor(this->y);
}
void creep::setX(double new_x){
	this->x = new_x;
}
void creep::setY(double new_y){
	this->y = new_y;
}
double creep::getXd()
{
	return x;
}
double creep::getYd()
{
	return y;
}
int creep::damage(int d, int a)
{
	int calcD = d;
	if(a >= this->armor)
	{
		calcD = calcD - (this->getArmor() - a);
	}
	else
	{
		calcD = 0;
	}
	this->health = this->health - calcD;
	if(health <= 0)
	{
		health = 0;
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
	if(Xdir == 0 && Ydir == 0)
	{
		p.pop();
		if(p.isEmpty())
		{
			cout << "creep has reached its goal, please kill it off\n";
			return true;
		}
		coord next = p.getNext();

		Xdir = next.x - prevPos.x;
		Ydir = next.y - prevPos.y;
	}

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

		double extra = (getYd() * Ydir) - ((next.y * GRID_SIZE * Ydir) + (BOARD_Y_OFFSET * Ydir));
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

		setY(prevPos.y * GRID_SIZE + BOARD_Y_OFFSET);
		setX(getXd() + (Xdir * extra));
		setY(getYd() + (Ydir * extra));
	}
	return false;
}

void creep::displayCreep(SDL_Surface *screen, SDL_Surface *image, SDL_Rect *spriteMap[ANIM_NUM])
{
	if(SDL_GetTicks() - timeOfLastUpdate >= 10000)
	{
		//this->kill();
	}
	if(image != NULL)
	{
		updateAnim();
		this->r->x = this->getX();
		this->r->y = this->getY();
		SDL_BlitSurface(image, spriteMap[animIndex], screen, r);
	}
	else
		cout << "No image for creep.\n";
}
void creep::updateAnim()
{
	if(animDelay == 0)
	{
		animIndex++;
		if(animIndex >= animCount)
			animIndex = 0;
		animDelay = animTiming;
	}
	else
		animDelay--;
}
void creep::recalcPath( vector<vector<bool> > nMap )
{
	if(nMap[p.getNext().x][p.getNext().y])
	{
		p.setStart(p.getNext());
		p.setSpec(prevPos);
		p.genPath(nMap,2);
	}
	else
	{
		p.setStart(p.getNext());
		p.genPath(nMap,1);
	}
	
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

int creep::getDir()
{
	if(Xdir == -1)
		return 0;
	else if(Ydir == 1)
		return 1;
	else if(Xdir == 1)
		return 2;
	else
		return 3;
}

void creep::kill()
{
	health = 0;
	setX(0);
	setY(0);
	alive = false;
}

void creep::setDir( int nDir )
{
	dispDir = nDir;
}

int creep::getDispDir()
{
	return dispDir;
}

int creep::getTimeout()
{
	return timeOfLastUpdate;
}

void creep::setUpdateTime( int nTime )
{
	timeOfLastUpdate = nTime;
}
void creep::setType(int newType)
{
	type = newType;
}
void creep::setLevel(int newLevel)
{
	level = newLevel;
}

coord creep::getPrev()
{
	return prevPos;
}
