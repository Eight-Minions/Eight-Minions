#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cmath>
#include <cstdarg>
#include <vector>

#include "SDL.h"
#include "SDL_net.h"
#include "SDL_image.h"
#include "c_list.h"
#include "UpdMess.h"
#include "path.h"

#define TCP_NODELAY 1 // THIS LINE FIXES SLOWNESS!!!!

//Update Message Constants
#define CREEP 0			// For an update on a creep
#define NEWCREEP 1		// For a new creep
#define TOWER 2			// For an update on a tower
#define TOWERATTACK 3	// For an update on a tower attack
#define PLAYERUPDATE 4	// For an update to the player
#define MAX_NUM_VAL 10	// Max number of values in a single update

//Creep type definitions
#define NUM_CREEPS 6 //the total number of creeps
#define NORM 0  // average everything
#define FAST 1  // low armor, low health, high speed, and medium numbers
#define TANK 2  // high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 // high armor, high health, average speed, very low numbers
#define FATTY 5 // low armor, high health, low speed, medium numbers (could probably come up with a better name)

//Spawn Tower Definitions
#define CREEPTOWERSTARTLEVEL 0

//Map Constants
#define MAPSIZE_X 35
#define MAPSIZE_Y 21
#define BOARD_X_OFFSET 38
#define BOARD_Y_OFFSET 38
#define GRID_SIZE 16

//number of buttons 
#define NUM_BUTTONS 10

//Movement Constant
#define CLOCK_CAP .50

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;
using std::list;
using std::vector;

SDL_Rect *newRect(int x, int y, int w, int h);

class location
{
private:
	double x;
	double y;
public:
	location();
	location(int new_x, int new_y);
	~location();
	int getX();
	int getY();
	double getXd();
	double getYd();
	void setX(double new_x);
	void setY(double new_y);
	coord gC(int x, int y);
};

#endif