#include "standard_tower.h"

Standard_Tower::Standard_Tower() : tower(){
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y) : tower(STANDARDTOWERSTARTLEVEL, -1, set_x, set_y){
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y, game_host *nManager) : tower(STANDARDTOWERSTARTLEVEL, -1, set_x, set_y){
	manager = nManager;
}
void Standard_Tower::damageClosestCreep(int radius)
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

//void Standard_Tower::damageClosestCreepToPosition(int radius, location position)
//{
//
//}
void Standard_Tower::damageNeighbors(int radius)
{
	/*
	list<creep> inRadius;
	cListNode<creep> *cur this->manager->creepList.getStart();
	while(cur != NULL)
	{
		double currentDistance = sqrt(pow((double)(((cur->getData().getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
			pow((double)(((cur->getData().getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
		if(currentDistance < radius)
		{
			
		}
	}
	*/
}
