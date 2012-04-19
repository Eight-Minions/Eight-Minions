#include "mine.h"

Mine::Mine() : structure()
{
}
Mine::Mine(int level, int player, int type, int set_x, int set_y) : structure(level, player, type, set_x, set_y)
{
	cost = updateCost(level);
}
Mine::Mine(int level, int player, int type, int set_x, int set_y, game_host *nManager) : structure(level, player, type, set_x, set_y)
{
	manager = nManager;
	cost = updateCost(level);
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
	cListNode<creep*> *curCreepNode = this->manager->getCreepList()->getStart();
	int compX, compY;
	while(curCreepNode != NULL)
	{
		compX = curCreepNode->getData()->getX();
		if((compX - BOARD_X_OFFSET > (this->getX() - 1) * GRID_SIZE) && (compX - BOARD_X_OFFSET < (this->getX() + 1) * GRID_SIZE))
		{
			compY = curCreepNode->getData()->getY();
			if((compY - BOARD_Y_OFFSET > (this->getY() - 1) * GRID_SIZE) && (compY - BOARD_Y_OFFSET < (this->getY() + 1) * GRID_SIZE))
				return true;
		}
		curCreepNode = curCreepNode->getNext();
	}
	return false;
}
bool Mine::upgrade()
{
	if(this->getLevel() < 5)
	{
		if(cost <= this->manager->getPlayer(this->getPlayer())->getMoney())
		{
			this->setLevel(this->getLevel() + 1);
			cost = updateCost(this->getLevel());
			return true;
		}
	}
	return false;
}
void Mine::choose()
{
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow(cur->getData()->getXd() - (this->getX() * GRID_SIZE + BOARD_X_OFFSET),2) + pow(cur->getData()->getYd() - (this->getY() * GRID_SIZE + BOARD_Y_OFFSET),2));
			if(currentDistance < range)
			{
				manager->sendMessageToQueue(UpdMess(this->getPlayer(),TOWER, TOWERATTACK, this->getX(), this->getY(), cur->getIndex(), AREAOFEFFECT).getMT());
				chosenCreeps.push(cur->getIndex());
			}
		}
		cur = cur->getNext();
	}
}

void Mine::doDamage()
{
	int frontNodeID = 0;
	cListNode<creep*> *frontNode= NULL;
	creep *frontCreep = NULL;
	while(chosenCreeps.empty() == false)
	{
		frontNodeID = chosenCreeps.front();
		if(this->manager->getCreepList()->checkForObjectWithID(frontNodeID) == true)
		{
			frontNode = this->manager->getCreepList()->getNodeWithID(frontNodeID);
			frontCreep = frontNode->getData();
			if(frontCreep != NULL)
			{
				if(frontCreep->isAlive() == true)
				{
					frontCreep->damage(damageValue);
					manager->sendMessageToQueue(UpdMess(frontCreep->getPlayer(), CREEP, frontNodeID, frontCreep->getX(), frontCreep->getY(), frontCreep->getHealth()).getMT());
					if(frontCreep->isAlive() == false)
					{
						int reward = frontCreep->getReward();
						int curMoney = manager->getPlayer(this->getPlayer())->getMoney();
						manager->getPlayer(this->getPlayer())->addMoney(frontCreep->getReward());
						// Update money value for player based on reward for killing the creep
						int newMony = this->manager->getPlayer(this->getPlayer())->getMoney();
						manager->sendMessageToQueue(UpdMess(this->getPlayer(), PLAYERUPDATE, manager->getPlayer(this->getPlayer())->getHealth(), manager->getPlayer(this->getPlayer())->getMoney()).getMT());

					}
				}
			}
		}
		chosenCreeps.pop();
	}
}
int Mine::getCost()
{
	return cost;
}
int Mine::updateCost(int cLevel)
{
	if(cLevel >= 0 && cLevel <= 4)
	{
		return mineArr[cLevel][4];
	}
	return 0;
}