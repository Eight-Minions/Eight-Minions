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
	int sellReward; 
	SDL_Rect *r; 
	bool passable;
	bool paused;
public:
	structure();
	structure(int level, int player, int type, int x, int y);
	~structure();

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
	bool isPaused();
	void pause();
	void unpause();

	virtual void iterate()
	{
		cout << "Nothing to do for base tower type" << endl;
	}
	/*
	virtual void pause()
	{
		cout << "Nothing to do for base tower type" << endl;
	}
 	virtual void unpause()
	{
		cout << "Nothing to do for base tower type" << endl;
	}
	*/
 	virtual bool upgrade()
	{
		cout << "Nothing to do for base tower type" << endl;
		return false;
	}
	virtual bool upgradeClient()
	{
		cout << "Nothing to do for base tower type" << endl;
		return false;
	}
	virtual bool changeType(int newType)
	{
		cout << "Nothing to do for base tower type" << endl;
		return false;
	}
	virtual bool changeTypeClient(int newType)
	{
		cout << "Nothing to do for base tower type" << endl;
		return false;
	}

	int setLevel(int newLevel);


	void displayTower(SDL_Surface *screen, SDL_Surface* image);
};
#endif 