#include "standard_tower.h"

Standard_Tower::Standard_Tower() : tower()
{
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y) : tower(STANDARDTOWERSTARTLEVEL, p, -1, set_x, set_y)
{
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y, game_host *nManager) : tower(STANDARDTOWERSTARTLEVEL, p, -1, set_x, set_y)
{
	manager = nManager;
}
void Standard_Tower::chooseClosestCreep(double radius)
{
	
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	creep *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
			if(currentDistance < distanceClosest)
			{
				closestCreep = cur->getData();
				distanceClosest = currentDistance;
			}
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL)
		chosenCreeps.push(closestCreep);
}
void Standard_Tower::chooseClosestCreepToPosition(double radius, location position)
{
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	creep *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((position.getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((position.getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
			if(currentDistance < distanceClosest)
			{
				closestCreep = cur->getData();
				distanceClosest = currentDistance;
			}
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL)
		chosenCreeps.push(closestCreep);
}
void Standard_Tower::chooseNeighbors(double radius)
{
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();

	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
			if(currentDistance < radius)
			{
				chosenCreeps.push(cur->getData());
			}
		}
		cur = cur->getNext();
	}
}
void Standard_Tower::chooseNeighborsNearPosition(double radius, location position)
{
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();

	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((position.getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((position.getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
			if(currentDistance < radius)
			{
				chosenCreeps.push(cur->getData());
			}
		}
		cur = cur->getNext();
	}
}

/*
	choses creeps if the cool down is 0
	returns true if something was chosen
	returns false if nothing was chosen or the tick is not up.
*/
bool Standard_Tower::choose()
{
	if(coolDownTick <= 0)
	{
		if(attackStrategy == ATTACKCLOSESTTOTOWER)
		{
			if(attackType == AREAOFEFFECT)
			{
				this->chooseNeighbors(range);
			}
			else if(attackType == ATTACKONECREEP)
			{
				this->chooseClosestCreep(range);
			}
			else
				return false;
		}
		else if(attackStrategy == ATTACKCLOSESTTOBASE)
		{
			if(attackType == AREAOFEFFECT)
			{

			}
			else if(attackType == ATTACKONECREEP)
			{

			}
			else
				return false;
		}
		else
			return false;
		if(chosenCreeps.size() > 0)
		{
			coolDownTick = coolDownDuration;
			return true;  // Stuff was chosen
		}
		else
			return false; //Nothing was chosen. 
	}
	else
	{
		coolDownTick--;   //Next iteration
		return false;
	}
}
/*
	Does damage to creeps if the tick is 0
	Returns true if it should damage the creeps;
	Retruns false if it needs to go to the next iteration
*/
bool Standard_Tower::doDamage()
{
	if(attackTick <= 0)
	{
		while(chosenCreeps.size() > 0)
		{
			if(chosenCreeps.front() != NULL) // Does the creep still exist?
				chosenCreeps.front()->damage(damageValue);
			chosenCreeps.pop();
		}
		attackTick = attackDuration;
		return true;
	}
	else
	{
		attackTick--;
		return false;
	}
}