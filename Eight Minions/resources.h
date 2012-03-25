#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <cmath>
#include "SDL.h"
#include "SDL_net.h"
#include "SDL_image.h"
#include "c_list.h"
#include "UdpMess.h"


#define TCP_NODELAY 1 // THIS LINE FIXES SLOWNESS!!!!

#define MAPSIZE_X 35
#define MAPSIZE_Y 21

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;
using std::list;

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

// TL: Maybe a player class? We could have two with objects to hold their towers and creepers (health and money too?)
// TL: Probably in a different file tho...
// J: we probably will need some sort of a player class. approved.
// K: We could do different professions/specializations as well, examples would be one spec has stronger towers, another gets-
// K : currency faster or has stronger units.
// J: i like this idea.

#endif