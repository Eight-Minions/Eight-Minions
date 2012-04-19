#include "mine.h"

Mine::Mine() : Standard_Tower()
{
}
Mine::Mine(int level, int player, int type, int set_x, int set_y) : Standard_Tower(level, player, type, set_x, set_y)
{
}
Mine::Mine(int level, int player, int type, int set_x, int set_y, game_host *nManager) : Standard_Tower(level, player, type, set_x, set_y, nManager)
{
	manager = nManager;
}
Mine::~Mine()
{
}
void Mine::iterate()
{
	if(isOnTop())
	{
		choose();
		doDamage();
	}
}
bool Mine::isOnTop()
{
	cListNode<creep*> *curCreepNode = manager->getCreepList()->getStart();
	creep *curCreep = NULL;
	while(curCreepNode != NULL)
	{	
		curCreep = curCreepNode->getData();
		 
		return true;
		curCreepNode = curCreepNode->getNext();
	}
	return false;
}

bool Mine::upgrade()
{

	return false;
}