#include "tower.h"

tower::tower(int h, int l, int t, int set_x, int set_y){
	level = l;
	type = t;
	this->setX(set_x);
	this->setY(set_y);
}
int tower::getLevel(){
	return this->level;
}
int tower::getType(){
	return this->type;
}
tower::~tower(){
}
void tower::damageNeighbors(int radius){
	// TL:
	// Check the linkedlist for neightbors based upon its position
	// Insert them in a new linked list
	// Damage those neighbors
}
void tower::damageClosestCreep(int radius){
	// TL:
	// creep closest = NULL;
	// Check the linkedlist for the closest creep within some radius
	// closest.damage(this->attack * this->speed);
	// this->attack * this->speed because having some wait could be odd?
}


