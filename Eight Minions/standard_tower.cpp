#include "standard_tower.h"

Standard_Tower::Standard_Tower() : tower(){
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y) : tower(STANDARDTOWERSTARTLEVEL, -1, set_x, set_y){
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y, game_host *nManager) : tower(STANDARDTOWERSTARTLEVEL, -1, set_x, set_y){
	manager = nManager;
}
void Standard_Tower::damageClosestCreep(double radius)
{
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	creep *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
			pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
		if(currentDistance < distanceClosest)
		{
			closestCreep = cur->getData();
			distanceClosest = currentDistance;
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL){
		closestCreep->damage(damageValue);
	}
}
void Standard_Tower::damageClosestCreepToPosition(double radius, location position)
{
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	creep *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((position.getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
			pow((double)(((position.getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
		if(currentDistance < distanceClosest)
		{
			closestCreep = cur->getData();
			distanceClosest = currentDistance;
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL){
		closestCreep->damage(damageValue);
	}
}
void Standard_Tower::damageNeighbors(double radius)
{
	list<creep*> inRadius;
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
			pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
		if(currentDistance < radius)
		{
			inRadius.push_back(cur->getData());
		}
	}
	while(inRadius.size() > 0)
	{
		if(inRadius.back() != NULL)
		{
			inRadius.back()->damage(damageValue);
			inRadius.pop_back();
		}
	}
}
void Standard_Tower::damageNeighborsNearPosition(double radius, location position){
	list<creep*> inRadius;
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((position.getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
			pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((position.getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
		if(currentDistance < radius)
		{
			inRadius.push_back(cur->getData());
		}
	}
	while(inRadius.size() > 0)
	{
		if(inRadius.back() != NULL)
		{
			inRadius.back()->damage(damageValue);
			inRadius.pop_back();
		}
	}
}