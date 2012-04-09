#include "standard_tower.h"

Standard_Tower::Standard_Tower() : tower()
{
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y) : tower(l,t,set_x,set_y)
{
}
Standard_Tower::Standard_Tower(int l, int t, int set_x, int set_y, game_host *nManager) : tower(l,t,set_x,set_y, nManager)
{
}
void Standard_Tower::damageClosestCreep(int radius)
{
	/*
	int x_high =	getX() + radius;
	int x_low =		getX() - radius;
	int y_high =	getY() + radius;
	int y_low =		getY() - radius;
	int x_closest = -1;
	int y_closest = -1;
	int closestCreep = -1;
	double distanceClosest = 0;
	for(int i = 0; i < this->manager->creepList.maxIterator; i++)
	{
		if(manager->creepList.checkForObjectWithID(i))
		{
			int x_cur = manager->creepList.getObjectWithID(i)->getX(); // Convert from pixels to squares
			int y_cur = manager->creepList.getObjectWithID(i)->getY(); // Convert form pixels to squares
			if(x_high > x_cur && x_low < x_cur)
			{
				if(y_high > y_cur && y_low < y_cur)
				{
					if(closestCreep != -1)
					{
						double distanceCur = sqrt(pow(abs(x_cur - getX()), 2) + pow(abs(y_cur - getY()),2));	
						if(distanceCur < distanceClosest)
						{
							closestCreep = i;
							x_closest = x_cur;
							y_closest = y_cur;
						}
					}
					else
					{
						closestCreep = i;
						x_closest = x_cur;
						y_closest = y_cur;
					}
				}
			}
		}
	}
	*/
}
void Standard_Tower::damageClosestCreepToPosition(int radius, location position)
{

}
void Standard_Tower::damageNeighbors(int radius)
{

}