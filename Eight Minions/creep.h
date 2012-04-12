#ifndef CREEP_H
#define CREEP_H

#include "resources.h"

class creep : public location
{
private:
	int player;
	int health;
	int armor;
	int speed;
	int level;
	int type;
	int reward;

	bool alive;

	int Xdir;
	int Ydir;

	SDL_Surface *img;
	SDL_Rect *r; //could we include this rect inside the locations class? it would be nice
	coord prevPos;

	int animIndex;
	int animTiming;
	int animCount;
public:
	Path p;
	
	creep(int type, int pl, int level, int x, int y);
	creep();
	~creep();

	bool move();
	void recalcPath(vector<vector<bool>> nMap);

	int damage(int damage);
	int getHealth();
	int setHealth(int newHealth);
	int getPlayer();

	int getReward();

	void displayCreep(SDL_Surface *screen, SDL_Surface *images[4]);
	void updateAnim();

	void setPlayer(int p); // Not sure where I would ever use this...
	int getType();
	int getLevel();
	bool isAlive();
};

#endif