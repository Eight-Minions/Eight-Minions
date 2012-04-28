#ifndef CREEP_H
#define CREEP_H

#include "resources.h"

class creep
{
private:
	int player;
	int health;
	int tempHealth;
	int armor;
	int speed;
	int level;
	int type;
	int reward;
	int price;

	bool alive;
	creepStatus cStat;

	int timeOfLastUpdate;

	int Xdir;
	int Ydir;
	int dispDir;

	SDL_Rect *r; 
	coord prevPos;

	int animIndex;
	int animTiming;
	int animDelay;
	int animCount;

	double x;
	double y;
public:
	Path p;
	
	creep(int type, int pl, int level, int x, int y);
	creep();
	~creep();

	int getX();
	int getY();
	double getXd();
	double getYd();
	void setX(double new_x);
	void setY(double new_y);

	bool move();
	void recalcPath(vector<vector<bool> > nMap);

	int damage(int damage, int armorPen);
	void kill();

	void displayCreep(SDL_Surface *screen, SDL_Surface *image, SDL_Rect *spriteMap[ANIM_NUM]);
	void updateAnim();
	void updateStatus();
	void setStatus(creepStatus newStat);

	int getHealth();
	int setHealth(int newHealth);
	int getPlayer();
	void setPlayer(int p);
	int getType();
	void setType(int newType);
	int getLevel();
	void setLevel(int newLevel);
	int getArmor();	
	int getReward();
	int getPrice();
	int getDir();
	coord getPrev();

	int getTimeout();
	void setUpdateTime(int nTime);

	bool isAlive();
	void setDir( int nDir );
	int getDispDir();
	int getTempHealth();
	int tempDamage(int d, int a);
};

#endif