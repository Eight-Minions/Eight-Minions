#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <conio.h>
#include "SDL.h"
#include "SDL_net.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class location
{
private:
	int x;
	int y;
public:
	location();
	int getX();
	int getY();
	void setX(int new_x);
	void setY(int new_y);
};


//using namespace std; //Oh really? - it was just to test something, forgot to change back  -- haha okay I was gonna have a chat with you :P

#endif