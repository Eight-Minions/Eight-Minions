#ifndef RESOURCES_H
#define RESOURCES_H

#include <fstream>
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
#include "FadeMessage.h"

//to calculate total number of lines, press ctrl + shift + f and search .cpp and .h files for the regular expression ^:b*[^:b#/]+.*$

#define TCP_NODELAY 1 // THIS LINE FIXES SLOWNESS!!!!

//Standard UpdMess Definitions
#define CREEP 0				// For an update on a creep
#define NEWCREEP 1			// For a new creep
#define PLAYERUPDATE 2		// For an update to the player
#define TOWER 3 			// For anything to do with a tower
#define GAMEOVER 4			// Sends the winning player
#define BASE 5				// Base updates
#define CREEPUPDATE 6		// Sends a full update of one creep's values

// Base UpdMess Definitions
#define UPGRADE 0
#define ADDTYPE 1



// Tower UpdMess Definitions
#define TOWERCREATION 0
#define TOWERATTACK 1
#define TOWERPLACE 2
#define TOWERUPGRADE 3
#define TOWERCHANGE 4
#define TOWERTOGGLE 5
#define TOWERDELETE 6
#define TOWERSTRATEGY 7
#define MINEPLACE 8
#define OBSTACLEPLACE 9

//Creep type definitions
#define NUM_CREEPS 6 //the total number of creeps
#define NORM 0  // average everything
#define FAST 1  // low armor, low health, high speed, and medium numbers
#define TANK 2  // high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 // high armor, high health, average speed, very low numbers
#define FATTY 5 // low armor, high health, low speed, medium numbers (could probably come up with a better name)

// Base Definitions
#define BASEUPGRADECOST 220
#define ADDFAST 40
#define ADDTANK 90
#define ADDSWARM 50
#define ADDTITAN 250
#define ADDFATTY 80
const int addSpawnArr[NUM_CREEPS] = {0, ADDFAST, ADDTANK, ADDSWARM, ADDTITAN, ADDFATTY};

// Tower Type Constants
#define NUM_TOWERS 12
// Structure 
#define STRUCTURE 0
//
#define STRUCTURESTARTLEVEL 1
//*******Attack Towers*******
#define NORMTOWER 1
#define FASTTOWER 2
#define AOETOWER 3
#define HEAVYTOWER 4
//*******Mine Towers ******
#define MINETOWER 5
#define MINETOWERSTARTLEVEL 1
//
#define STANDARDTOWERSTARTLEVEL 1
//*******Spawners and Spawner Towers*******
const int creepBaseSpawnNum[NUM_CREEPS] = {8,9,5,8,2,5};
//Spawn Tower Definitions
#define NORMCREEPTOWER 6
#define FASTCREEPTOWER 7
#define TANKCREEPTOWER 8
#define SWARMCREEPTOWER	9
#define TITANCREEPTOWER 10
#define FATTYCREEPTOWER 11
//
#define CREEPTOWERSTARTLEVEL 1
#define CREEPTOWERDELAY 20
#define GETCREEPTYPE 6 // Subtract 5 to get the creep type
//*******Effect Towers*******
#define SLOWTOWER 12
#define SPEEDTOWER 13
#define HEALTOWER 14

//*******Obstacles*******
#define OBSTACLE 20

//Animation
#define ANIM_NUM 6

#define MAX_FPS 20

#define MAXCREEPLEVEL 5
#define MAXCREEPVARIABLES 6

//Creep types
// Health Armor Speed Reward Price Spawn
const int normCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{2,0,2,2,1,2},		{8,1,3,3,2,2},		{12,2,3,6,4,2},		{20,3,4,12,6,2},	{30,4,5,15,8,2}};
const int fastCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{3,0,4,1,1,2},		{4,0,5,2,2,2},		{9,1,5,4,4,2},		{12,1,6,8,6,2},		{18,2,7,10,8,2}};
const int tankCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{5,1,1,2,2,3},		{8,2,1,5,3,3},		{12,3,2,10,6,3}, 	{20,4,2,15,12,3},	{36,5,3,20,16,3}};
const int swarmCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES]=		{{2,0,3,1,1,1},		{3,0,3,1,1,1},		{5,1,4,2,2,1},		{10,1,5,3,3,1},		{20,2,6,4,4,1}};
const int fattyCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{12,0,1,2,1,3},	{18,1,1,5,3,3},		{22,2,2,10,6,3},	{35,3,2,15,10,3},	{50,4,3,20,14,3}};
const int titanCreepArr[MAXCREEPLEVEL][MAXCREEPVARIABLES] =		{{15,2,2,5,6,5},	{25,3,2,15,14,5},	{50,4,3,25,25,5},	{80,5,3,50,50,5},	{120,7,4,100,150,5}};

//Map Constants
#define MAPSIZE_X 26
#define MAPSIZE_Y 20
#define BOARD_X_OFFSET 8
#define BOARD_Y_OFFSET 56
#define GRID_SIZE 24

//Screen Size Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608

//Number of Buttons 
#define NUM_BUTTONS 30

//Number of text objects
#define TEXT_NUM 35

//Movement Constant
#define CLOCK_CAP .45

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

//Tower Types
// Damage ArmorPenetration Range Speed Cost
const int basicArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{1,0,(3 * GRID_SIZE),40,5},	{3,1,(4 * GRID_SIZE),35,10},			{5,1,(4 * GRID_SIZE),30,22},	{10,2,(5 * GRID_SIZE),25,50},			{20, 3, (int)(5.5 * GRID_SIZE), 20, 120}};
const int fastArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{1,0,(3 * GRID_SIZE),30,7},	{2,0,(3 * GRID_SIZE),25,12},			{4,1,(3 * GRID_SIZE),20,24},	{8,1,(4 * GRID_SIZE),15,60},			{15,2,(4 * GRID_SIZE),10,150}};
const int areaOfEffectArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =	{{1,0,(2 * GRID_SIZE),80,30},	{2,0,(2 * GRID_SIZE),70,45},			{4,1,(2 * GRID_SIZE),60,60},	{6,1,(int)(2.5 * GRID_SIZE),50,150},	{15,2,(3 * GRID_SIZE),45,200}};
const int heavyArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{2,1,(2 * GRID_SIZE),60,15},	{4,2,(3 * GRID_SIZE),54,25},			{9,3,(4 * GRID_SIZE),48,40},	{13,4,(5 * GRID_SIZE),40,100},			{22,5,(int)(5.5 * GRID_SIZE),30,300}};
const int mineArr[MAXTOWERLEVEL][MAXTOWERVARIABLES] =			{{5,2,(1 * GRID_SIZE),0,3},		{10,3,((int)(1.5 * GRID_SIZE)),0,5},	{15,4,(2 * GRID_SIZE),0,8},		{20,5,((int)(2.5 * GRID_SIZE)),0,10},	{25,6,(3 * GRID_SIZE),0,15}};


#define basicArrd			{{1,0,(3 * GRID_SIZE),40,5},	{3,1,(4 * GRID_SIZE),35,10},			{5,1,(4 * GRID_SIZE),30,22},	{10,2,(5 * GRID_SIZE),25,50},			{20, 3, (int)(5.5 * GRID_SIZE), 20, 120}}
#define fastArrd			{{1,0,(3 * GRID_SIZE),30,7},	{2,0,(3 * GRID_SIZE),25,12},			{4,1,(3 * GRID_SIZE),20,24},	{8,1,(4 * GRID_SIZE),15,60},			{15,2,(4 * GRID_SIZE),10,150}}
#define areaOfEffectArrd	{{1,0,(2 * GRID_SIZE),60,30},	{2,0,(2 * GRID_SIZE),54,45},			{4,1,(2 * GRID_SIZE),50,60},	{6,1,(int)(2.5 * GRID_SIZE),45,150},	{15,2,(3 * GRID_SIZE),36,200}}
#define heavyArrd			{{2,1,(2 * GRID_SIZE),60,15},	{4,2,(3 * GRID_SIZE),54,25},			{9,3,(4 * GRID_SIZE),48,40},	{13,4,(5 * GRID_SIZE),40,100},			{22,5,(int)(5.5 * GRID_SIZE),30,300}}
#define mineArrd			{{5,2,(1 * GRID_SIZE),0,3},		{10,3,((int)(1.5 * GRID_SIZE)),0,5},	{15,4,(2 * GRID_SIZE),0,8},		{20,5,((int)(2.5 * GRID_SIZE)),0,10},	{25,6,(3 * GRID_SIZE),0,15}}


/*const int towerArrays[5][MAXTOWERLEVEL][MAXTOWERVARIABLES] =	{{{1,0,(3 * GRID_SIZE),40,5},	{3,1,(4 * GRID_SIZE),35,10},			{5,1,(4 * GRID_SIZE),30,22},	{10,2,(5 * GRID_SIZE),25,50},			{20, 3, (int)(5.5 * GRID_SIZE), 20, 120}},
																{{1,0,(3 * GRID_SIZE),30,7},	{2,0,(3 * GRID_SIZE),25,12},			{4,1,(3 * GRID_SIZE),20,24},	{8,1,(4 * GRID_SIZE),15,60},			{15,2,(4 * GRID_SIZE),10,150}},
																{{1,0,(2 * GRID_SIZE),60,12},	{2,0,(2 * GRID_SIZE),54,45},			{4,1,(2 * GRID_SIZE),50,60},	{6,1,(int)(2.5 * GRID_SIZE),45,150},	{15,2,(3 * GRID_SIZE),36,200}},
																{{2,1,(2 * GRID_SIZE),60,15},	{4,2,(3 * GRID_SIZE),54,25},			{9,3,(4 * GRID_SIZE),48,40},	{13,4,(5 * GRID_SIZE),40,100},			{22,5,(int)(5.5 * GRID_SIZE),30,300}},
																{{5,2,(1 * GRID_SIZE),0,3},		{10,3,((int)(1.5 * GRID_SIZE)),0,5},	{15,4,(2 * GRID_SIZE),0,8},		{20,5,((int)(2.5 * GRID_SIZE)),0,10},	{25,6,(3 * GRID_SIZE),0,15}}};

*/
const int towerArrays[5][MAXTOWERLEVEL][MAXTOWERVARIABLES] =	{basicArrd,fastArrd,areaOfEffectArrd,heavyArrd,mineArrd};
const int towerDelays[5] =			{20,15,6,30,2};
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
using std::fstream;
using std::ofstream;
using std::ifstream;

SDL_Rect *newRect(int x, int y, int w, int h);
SDL_Color makeColor(int r, int g, int b);
SDL_Surface *LoadImageCK(string filename);

class structure;
class game_host;
class Spawner;

#endif