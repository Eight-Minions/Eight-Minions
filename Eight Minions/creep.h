#ifndef CREEP_H
#define CREEP_H

#include "resources.h"

class creep
{
private:
	int player;
	int health;
	int armor;
	int speed;
	int level;
	int type;
	int reward;
	int price;

	bool alive;

	int Xdir;
	int Ydir;
	int dispDir;

	SDL_Rect *r; //could we include this rect inside the locations class? it would be nice
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
	coord gC(int x, int y);

	bool move();
	void recalcPath(vector<vector<bool>> nMap);

	int damage(int damage);
	void kill();

	void displayCreep(SDL_Surface *screen, SDL_Surface *image, SDL_Rect *spriteMap[ANIM_NUM]);
	void updateAnim();

	int getHealth();
	int setHealth(int newHealth);
	int getPlayer();
	void setPlayer(int p);
	int getType();
	int getLevel();
	int getArmor();	
	int getReward();
	int getPrice();
	int getDir();

	bool isAlive();
	void setDir( int nDir );
	int getDispDir();
};

#endif