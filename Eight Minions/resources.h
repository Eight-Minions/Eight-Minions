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
#define PURCHASEREQUEST 5 //from the client to the server, request to purchase something
#define MAX_NUM_VAL 10	// Max number of values in a single update

//Creep type definitions
#define NUM_CREEPS 6 //the total number of creeps
#define NORM 0  // average everything
#define FAST 1  // low armor, low health, high speed, and medium numbers
#define TANK 2  // high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 // high armor, high health, average speed, very low numbers
#define FATTY 5 // low armor, high health, low speed, medium numbers (could probably come up with a better name)

//Animation
#define ANIM_NUM 4

#define MAXCREEPLEVEL 5
#define MAXCREEPVARIABLES 5

//Creep types
// Health Armor Speed Reward Price
const int normCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{3,0,2,1,2},	{5,1,3,3,5},	{8,2,3,6,10},	{12,3,4,12,15},	{20,4,5,15,20}};
const int fastCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{2,0,4,1,3},	{3,0,5,2,5},	{5,1,5,4,8},	{8,1,6,8,12},	{12,2,7,10,15}};
const int tankCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{3,1,1,2,4},	{5,2,1,5,8},	{8,3,2,10,16},	{12,4,2,15,22},	{20,5,3,20,28}};
const int swarmCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES]=		{{2,0,3,1,2},	{3,0,3,1,3},	{5,1,4,2,4},	{8,1,4,2,5},	{10,2,5,3,6}};
const int fattyCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{5,0,1,2,3},	{8,1,1,5,7},	{11,2,2,10,15},	{15,3,2,15,21},	{25,4,3,20,27}};
const int titanCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{10,2,2,5,10},	{20,3,2,15,25},	{35,4,3,25,50},	{50,5,3,50,100},{100,7,4,100,250}};

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

//Number of Buttons 
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

//Attack Towers
#define BASICTOWER 0
#define FASTTOWER 1
#define AOETOWER 2
#define HEAVYTOWER 3
#define MINETOWER 4
//Spawner Towers
#define SPAWNERTOWER 5


//Tower Types
// Damage ArmorPenetration Range Speed Cost
const int basicArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{1,0,(3 * GRID_SIZE),60,5},	{3,1,(4 * GRID_SIZE),60,10},		{5,1,(4 * GRID_SIZE),50,22},	{10,2,(5 * GRID_SIZE),45,50},			{20, 3, (int)(5.5 * GRID_SIZE), 35, 120}};
const int fastArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{1,0,(3 * GRID_SIZE),40,7},	{2,0,(3 * GRID_SIZE),35,12},		{4,1,(3 * GRID_SIZE),30,24},	{8,1,(4 * GRID_SIZE),25,60},			{15,2,(4 * GRID_SIZE),15,150}};
const int areaOfEffectArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =	{{1,0,(2 * GRID_SIZE),90,12},	{2,0,(2 * GRID_SIZE),80,20},		{4,1,(2 * GRID_SIZE),75,30},	{6,1,(int)(2.5 * GRID_SIZE),70,70},		{15,2,(3 * GRID_SIZE),55,180}};
const int heavyArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{2,1,(2 * GRID_SIZE),90,15},	{4,2,(3 * GRID_SIZE),80,25},		{9,3,(4 * GRID_SIZE),70,40},	{13,4,(5 * GRID_SIZE),60,100},			{22,5,(int)(5.5 * GRID_SIZE),50,300}};
const int mineArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{5,2,(1 * GRID_SIZE),0,3},		{10,3,((int)(1.5 * GRID_SIZE)),0,5},	{15,4,(2 * GRID_SIZE),0,8},		{20,5,((int)(2.5 * GRID_SIZE)),0,10},		{25,6,(3 * GRID_SIZE),0,15}};

#define BASICATTACKDELAY 30
#define FASTATTACKDELAY 20
#define AOEATTACKDELAY 10
#define HEAVYATTACKDELAY 45
#define MINEATTACKDELAY 2


// Usings
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;
using std::list;
using std::vector;

SDL_Rect *newRect(int x, int y, int w, int h);
SDL_Color makeColor(int r, int g, int b);
SDL_Surface *LoadImageCK(string filename);
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