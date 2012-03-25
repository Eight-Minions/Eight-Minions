#include "resources.h"

location::location(){
	x = 0;
	y = 0;
}
location::location(int new_x, int new_y){
	x = new_x;
	y = new_y;
}
location::~location(){
}
int location::getX(){
	return (int)floor(this->x);
}
int location::getY(){
	return (int)floor(this->y);
}
void location::setX(double new_x){
	this->x = new_x;
}
void location::setY(double new_y){
	this->y = new_y;
}

double location::getXd()
{
	return x;
}

double location::getYd()
{
	return y;
}

