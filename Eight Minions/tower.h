#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class structure
{	
private:
	int player;
	int level;
	int type;
	int cost;
	int sellReward; 
	SDL_Rect *r; 
	bool passable;
	double x;
	double y;

	bool alive;
protected:
	bool paused;
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
	int getCost();
	void setSellReward(int newReward);
	int getSellReward();

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


	void displayTower(SDL_Surface *screen, SDL_Surface* image);
};
#endif 