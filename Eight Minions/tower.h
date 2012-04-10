#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class tower : public location
{	
private:
	int level;
	int type;
	SDL_Surface *img;
	SDL_Rect *r; 
public:
	tower();
	tower(int level, int type, int x , int y);
	~tower();

	int getLevel();
	int getType();
	int setType(int newType);

	void displayTower(SDL_Surface *screen);
};
#endif 