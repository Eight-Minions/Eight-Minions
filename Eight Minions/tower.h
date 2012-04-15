#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class structure : public location
{	
private:
	int player;
	int level;
	int type;
	SDL_Surface *img;
	SDL_Rect *r; 
	bool passable;
public:
	structure();
	structure(int level, int player, int type, int x, int y);
	~structure();

	int getLevel();
	int getType();
	int setType(int newType);
	int getPlayer();

	bool getPassable();
	void setPassable(bool nPass);

	int setLevel(int newLevel);

	virtual void iterate();

	void displayTower(SDL_Surface *screen);
};
#endif 