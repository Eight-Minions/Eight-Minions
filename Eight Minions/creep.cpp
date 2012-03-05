#include "creep.h"


creep::creep(){
}
creep::creep(int t, int l, int set_x, int set_y){
	type = t;
	level = l;
	health = 0;
	speed = 0;
	this->setX(set_x);  // Should probably have a generic starting point for each side 
	this->setY(set_y);
	// TL: just some more ideas
	if(type == TANK){
		health = 50;
		speed = 1;
	}
	else if(type == FAST){
		health = 30;
		speed = 2;
	}
	health = health * level;
	// Calculate path.
}
creep::~creep(){
	// Kill off that Queue?
}

int creep::damage(int d){
	this->health = this->health - d;
	if(this->health <= 0){
		// Remove from the list of creeps
		// Kill this object
		return 0;
	}
	return this->health;
}
void creep::move(){
	// Calculate Path;
	// Move one step forward or two if it is fast
}

void calculatePath(){
	// Update that queue
}