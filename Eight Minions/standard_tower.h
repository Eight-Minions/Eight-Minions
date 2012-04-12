#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include "UpdMess.h"

// Attack Types
#define ATTACKCLOSESTTOTOWER	1
#define ATTACKCLOSESTTOBASE		2
#define AREAOFEFFECT			1
#define ATTACKONECREEP			2

// Tower Constants
#define MAXLEVEL 5
#define MAXVARIABLES 5

#define BASIC 0
#define FAST 1
#define AOE 2
#define MINE 3

//Tower Types
// Damage ArmorPenetration Range Speed Cost
const int basicArr[MAXLEVEL][MAXVARIABLES] =			{{1,0,3,30,5},{3,1,3,25,10},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int fastArr[MAXLEVEL][MAXVARIABLES] =				{{1,0,3,20,7},{2,0,2,17,15},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int areaOfEffectArr[MAXLEVEL][MAXVARIABLES] =		{{1,0,2,45,12},{2,1,2,40,20},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
const int mineArr[MAXLEVEL][MAXVARIABLES] =				{{5,2,1,0,3},{10,4,1,0,6},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

class Standard_Tower : public tower
{
public:
	Standard_Tower();
	Standard_Tower(int l, int p, int t, int set_x, int set_y);
	Standard_Tower(int l, int p, int t, int set_x, int set_y, game_host *nManager);
	void chooseClosestCreep(double radius);
	void chooseClosestCreepToPosition(double radius, location position);
	void chooseNeighbors(double radius);
	void chooseNeighborsNearPosition(double radius, location position);
	bool choose();
	bool doDamage();
	void upgrade();
	void changeType();
private:
	game_host *manager;
	queue<cListNode<creep*>*> chosenCreeps;

	int damageValue;
	int attackType;
	double range;

	int coolDownTick;
	int coolDownDuration;

	int attackTick;
	int attackStrategy;
	int attackDuration;
};

#endif