#ifndef TOWER_H
#define TOWER_H
#include "resources.h"

class game_host;

class tower : public location
{	
private:
	int level;
	int type;
	SDL_Surface *img;
	SDL_Rect *r; 
	game_host *manager;
public:
	tower();
	tower(int level, int type, int x , int y); //constructor for clients
	tower(int level, int type, int x , int y, game_host *nManager);//constructor for game_host
	~tower();

	int getLevel();
	int getType();
	int setType(int newType);

	void displayTower(SDL_Surface *screen);
};


#endif 