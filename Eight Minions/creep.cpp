#include "creep.h"

creep::creep(int t, int l, int set_x, int set_y){
	type = t;
	level = l;
	health = 0;
	speed = 0;
	attack = 0;
	this->setX(set_x);
	this->setY(set_y);
	//T: I would like to use something like this so we can have differnt types with different health and speed and what not...
	//J: sounds good to me
	/*
	if(t == 1{
		health  = 100;
		
	}*/
	
}
creep::~creep(){
}
