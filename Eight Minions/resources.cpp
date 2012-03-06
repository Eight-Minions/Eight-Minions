#include "resources.h"

location::location(){
	x = 0;
	y = 0;
}
int location::getX(){
	return this->x;
}
int location::getY(){
	return this->y;
}
void location::setX(int new_x){
	this->x = new_x;
}
void location::setY(int new_y){
	this->y = new_y;
}

