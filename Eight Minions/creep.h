#ifndef CREEP_H
#define CREEP_H

#include "resources.h"
#include "path.h"



class creep : public location
{
private:
	int health;
	int armor;
	int speed;
	int level;
	int type;
	int attack;
	int Xdir;
	int Ydir;
	SDL_Surface *img;
	SDL_Rect *r; //could we include this rect inside the locations class? it would be nice
	coord prevPos;
	int animIndex;
public:
	Path p;

	creep(int type, int level, int x, int y);
	creep();
	~creep();

	bool move();
	void recalcPath(vector<vector<bool>> nMap);

	int damage(int damage);
	int getHealth();
	int setHealth(int newHealth);

	void displayCreep(SDL_Surface *screen);
	void updateAnim();
};

#endif