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

#define MAXCREEPLEVEL 5
#define MAXCREEPVARIABLES 5

//Creep types
// Health Armor Speed Reward Price
const int normCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{3,0,2,1,2},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int fastCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{2,0,4,1,2},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int tankCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{5,0,1,2,4},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int swarmCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{3,1,1,2,4},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int fattyCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{1,0,3,1,2},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int titanCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

//Spawn Tower Definitions
#define CREEPTOWERSTARTLEVEL 1
#define STANDARDTOWERSTARTLEVEL 1

//Map Constants
#define MAPSIZE_X 26
#define MAPSIZE_Y 20
#define BOARD_X_OFFSET 0
#define BOARD_Y_OFFSET 63
#define GRID_SIZE 24

//Screen Size Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608

//number of buttons 
#define NUM_BUTTONS 10

//Movement Constant
#define CLOCK_CAP .50

//Player Base Location
#define PLAYERONEX 0
#define PLAYERONEY 10
#define PLAYERTWOX 25
#define PLAYERTWOY 10

// Attack Types
#define ATTACKCLOSESTTOTOWER	1
#define ATTACKCLOSESTTOBASE		2
#define AREAOFEFFECT			1
#define ATTACKONECREEP			2

// Tower Constants
#define MAXTOWERLEVEL 5
#define MAXTOWERVARIABLES 5

#define BASICTOWER 0
#define FASTTOWER 1
#define AOETOWER 2
#define MINETOWER 3

//Tower Types
// Damage ArmorPenetration Range Speed Cost
const int basicArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =				{{1,0,(int)(3 * GRID_SIZE),30,5},{3,1,(int)(3.5 * GRID_SIZE),25,10},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int fastArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =				{{1,0,(int)(3 * GRID_SIZE),20,7},{2,0,(int)(2 * GRID_SIZE),17,15},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int areaOfEffectArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =		{{1,0,(int)(2 * GRID_SIZE),45,12},{2,1,(int)(2 * GRID_SIZE),40,20},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int mineArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =				{{5,2,(int)(1 * GRID_SIZE),0,3},{10,4,(int)(1 * GRID_SIZE),0,6},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;
using std::list;
using std::vector;

SDL_Rect *newRect(int x, int y, int w, int h);
SDL_Color makeColor(int r, int g, int b);

class tower;
class game_host;
class Spawner;

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