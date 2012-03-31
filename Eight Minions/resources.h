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

#define TCP_NODELAY 1 // THIS LINE FIXES SLOWNESS!!!!

#define MAPSIZE_X 35
#define MAPSIZE_Y 21

#define CREEP 0
#define TOWER 1
#define TOWERATTACK 2

#define NORM 0  // average everything
#define FAST 1  // low armor, low health, high speed, and medium numbers
#define TANK 2  // high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 // high armor, high health, average speed, very low numbers
#define FATTY 5 // low armor, high health, low speed, medium numbers (could probably come up with a better name)

#define BOARD_X_OFFSET 38
#define BOARD_Y_OFFSET 38

#define CLOCK_CAP .15

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;
using std::list;
using std::vector;

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
};

#endif