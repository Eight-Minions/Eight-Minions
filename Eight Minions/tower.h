#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class structure : public location
{	
private:
	int player;
	int level;
	int type;
	int cost;
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
	int getCost();

	int calculateCost(int cType);

	bool getPassable();
	void setPassable(bool nPass);

	virtual void iterate();
	virtual bool isPaused();
	virtual void pause();
	virtual void unpause();
	virtual bool upgrade();
	virtual bool upgradeClient();
	virtual bool changeType(int newType);
	virtual bool changeTypeClient(int newType);

	int setLevel(int newLevel);


	void displayTower(SDL_Surface *screen, SDL_Surface* image);
};
#endif 