#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class structure
{	
private:
	int player;

	int cost;
	int sellReward; 
	SDL_Rect *r; 
	bool passable;
	double x;
	double y;
	bool alive;


protected:
	int level;
	int type;

	bool paused;
	int anim_delay;
	int animIndex;
	int killcount;

public:
	structure();
	structure(int level, int player, int type, int x, int y);
	~structure();

	int getX();
	int getY();
	double getXd();
	double getYd();
	void setX(double new_x);
	void setY(double new_y);

	int getLevel();
	int getType();
	int setType(int newType);
	int getPlayer();
	virtual int getCost();
	void setSellReward(int newReward);
	int getSellReward();
	SDL_Rect *getr();

	int calculateCost(int cType);

	bool getPassable();
	void setPassable(bool nPass);

	virtual bool isPaused();
	virtual void pause();
	virtual void unpause();

	virtual void iterate();
 	virtual bool upgrade();
	virtual bool upgradeClient();
	virtual bool changeType(int newType);
	virtual bool changeTypeClient(int newType);
	
	void kill();

	int setLevel(int newLevel);

	bool isAlive();

	SDL_Rect *animRects[4];
	void displayTower(SDL_Surface *screen, SDL_Surface* image);
	int getKillcount();
	int updateCost(int uLevel, int uType);
};
#endif 