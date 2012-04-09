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
	for(int i = 0; i < this->creepList.size(); i++)
	{
		// if creep is in range
			creepList[i].damage(amount);
	}
	*/
}
void Standard_Tower::damageClosestCreepToPosition(int radius, location position)
{

}
void Standard_Tower::damageNeighbors(int radius)
{

}