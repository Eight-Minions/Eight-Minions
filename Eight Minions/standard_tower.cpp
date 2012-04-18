#include "standard_tower.h"

Standard_Tower::Standard_Tower() : structure()
{
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y) : structure(STANDARDTOWERSTARTLEVEL, p, t, set_x, set_y)
{
	changeType(t);
	attackTick = attackDuration;
	coolDownTick = coolDownDuration;
	this->setPassable(false);
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y, game_host *nManager) : structure(STANDARDTOWERSTARTLEVEL, p, t, set_x, set_y)
{
	manager = nManager;
	changeType(t);
	attackTick = attackDuration;
	coolDownTick = coolDownDuration;
	this->setPassable(false);
}
void Standard_Tower::chooseClosestCreep(double radius)
{
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	cListNode<creep*> *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow(cur->getData()->getXd() - (this->getX() * GRID_SIZE + BOARD_X_OFFSET),2) + pow(cur->getData()->getYd() - (this->getY() * GRID_SIZE + BOARD_Y_OFFSET),2));
			if(currentDistance < distanceClosest)
			{
				closestCreep = cur;
				distanceClosest = currentDistance;
			}
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL)
	{
		manager->sendMessageToQueue(UpdMess(this->getPlayer(),TOWER, TOWERATTACK, this->getX(), this->getY(), closestCreep->getIndex(), this->attackType).getMT());
		chosenCreeps.push(closestCreep->getIndex());
	}
}
void Standard_Tower::chooseClosestCreepToPosition(double radius, location position)
{
	double distanceClosest = radius;
	cListNode<creep*> *cur = NULL;
	cListNode<creep*> *closestCreep = NULL;

	cur = this->manager->getCreepList()->getStart();
	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow(cur->getData()->getXd() - (position.getX()),2) + pow(cur->getData()->getYd() - (position.getY()),2));
			if(currentDistance < distanceClosest)
			{
				closestCreep = cur;
				distanceClosest = currentDistance;
			}
		}
		cur = cur->getNext();
	}
	if(closestCreep != NULL)
	{
		manager->sendMessageToQueue(UpdMess(this->getPlayer(),TOWER, TOWERATTACK, this->getX(), this->getY(), closestCreep->getIndex(), this->attackType).getMT());
		chosenCreeps.push(closestCreep->getIndex());
	}
}
void Standard_Tower::chooseNeighbors(double radius)
{
	cListNode<creep*> *cur = this->manager->getCreepList()->getStart();

	while(cur != NULL)
	{
		if(cur->getData()->getPlayer() != this->getPlayer())
		{
			double currentDistance = sqrt(pow(cur->getData()->getXd() - (this->getX() * GRID_SIZE + BOARD_X_OFFSET),2) + pow(cur->getData()->getYd() - (this->getY() * GRID_SIZE + BOARD_Y_OFFSET),2));
			if(currentDistance < radius)
			{
				manager->sendMessageToQueue(UpdMess(this->getPlayer(),TOWER, TOWERATTACK, this->getX(), this->getY(), cur->getIndex(), this->attackType).getMT());
				chosenCreeps.push(cur->getIndex());
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
			double currentDistance = sqrt(pow(cur->getData()->getXd() - (position.getX()),2) + pow(cur->getData()->getYd() - (position.getY()),2));
			if(currentDistance < radius)
			{
				//Tower Attack:	UpdMess(Player[1], TOWERATTACK, AttackerX[2], AttackerY[2], AttackedID[4], AttackType[2]);
				manager->sendMessageToQueue(UpdMess(this->getPlayer(),TOWER, TOWERATTACK, this->getX(), this->getY(), cur->getIndex(), this->attackType).getMT());
				chosenCreeps.push(cur->getIndex());
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
				if(this->getPlayer() == 1) // Don't know if this is correct
				{
					this->chooseNeighborsNearPosition(range, location(PLAYERONEX, PLAYERONEY)); // Attack near own base
				}
				else if(this->getPlayer() == 2)
				{
					this->chooseNeighborsNearPosition(range, location(PLAYERTWOX, PLAYERTWOY));  // Attack near own base
				}
				else 
					return false;
			}
			else if(attackType == ATTACKONECREEP)
			{
				if(this->getPlayer() == 1)
				{
					this->chooseClosestCreepToPosition(range, location(PLAYERONEX, PLAYERTWOY)); // Attack near own base
				}	
				else if(this->getPlayer() == 2)
				{
					this->chooseClosestCreepToPosition(range, location(PLAYERONEX, PLAYERTWOY)); // Attack near own base
				}
				else 
					return false;
			}
			else
				return false;
		}
		else
			return false;
		if(chosenCreeps.size() > 0)
		{
			waiting = true;
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
	Returns false if it needs to go to the next iteration
*/
bool Standard_Tower::doDamage()
{
	int frontNodeID = 0;
	cListNode<creep*> *frontNode= NULL;
	creep *frontCreep = NULL;
	
	if(attackTick <= 0)
	{
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
		attackTick = attackDuration;
		waiting = false;
		return true;
	}
	else
	{
		attackTick--;
		return false;
	}
}
bool Standard_Tower::upgrade()
{
	if(getLevel() < 5)
	{
		if(manager->getPlayer(this->getPlayer())->getMoney() < cost)
			return false;
		else
		{
			manager->getPlayer(this->getPlayer())->spendMoney(cost);
			setLevel(getLevel() + 1);
			return changeType(getType()); // Doesn't actually change the type, just updates the values
		}
	}
	return false;
}
bool Standard_Tower::changeType(int newType)
{
	waiting = false;
	if(getLevel() >= 1 && getLevel() <= 5)
	{
		setType(newType);
		cost = updateCost(getLevel() - 1, getType());
		if(newType >= NORMTOWER && newType <= MINETOWER)
		{
			if(getType() == NORMTOWER)
			{
				damageValue =			basicArr[getLevel() - 1][0];
				armorPenetration =		basicArr[getLevel() - 1][1];
				range =					basicArr[getLevel() - 1][2];
				coolDownDuration =		basicArr[getLevel() - 1][3];
				attackDuration =		BASICATTACKDELAY;
				attackType  =			ATTACKONECREEP;
				attackStrategy =		ATTACKCLOSESTTOTOWER;
			}
			else if(getType() == FASTTOWER)
			{
				damageValue =			fastArr[getLevel() - 1][0];
				armorPenetration =		fastArr[getLevel() - 1][1];
				range =					fastArr[getLevel() - 1][2];
				coolDownDuration =		fastArr[getLevel() - 1][3];
				attackDuration =		FASTATTACKDELAY;
				attackType =			ATTACKONECREEP;
				attackStrategy =		ATTACKCLOSESTTOTOWER;
			}
			else if(getType() == AOETOWER)
			{
				damageValue =			fastArr[getLevel() - 1][0];
				armorPenetration =		fastArr[getLevel() - 1][1];
				range =					fastArr[getLevel() - 1][2];
				coolDownDuration =		fastArr[getLevel() - 1][3];
				attackDuration =		AOEATTACKDELAY;
				attackType =			AREAOFEFFECT;
				attackStrategy =		ATTACKCLOSESTTOTOWER;
			}
			else if(getType() == HEAVYTOWER)
			{
				damageValue =			heavyArr[getLevel() - 1][0];
				armorPenetration =		heavyArr[getLevel() - 1][1];
				range =					heavyArr[getLevel() - 1][2];
				coolDownDuration =		heavyArr[getLevel() - 1][3];
				attackDuration =		HEAVYATTACKDELAY;
				attackType =			ATTACKONECREEP;
				attackStrategy =		ATTACKCLOSESTTOTOWER;
			}
			else if(getType() == MINETOWER)
			{
				damageValue =			mineArr[getLevel() - 1][0];
				armorPenetration =		mineArr[getLevel() - 1][1];
				range =					mineArr[getLevel() - 1][2];
				coolDownDuration =		mineArr[getLevel() - 1][3];
				attackDuration =		MINEATTACKDELAY;
				attackType =			AREAOFEFFECT;
				attackStrategy =		ATTACKCLOSESTTOTOWER;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
	return true;
}
void Standard_Tower::iterate()
{
	if(waiting)
	{
		doDamage();
	}
	else
		choose();
}
int Standard_Tower::getCost()
{
	return cost;
}
int Standard_Tower::updateCost(int costLevel, int costType)
{
	if(costLevel >= 0 && costLevel <= 4)
	{
		if(costType == NORMTOWER)
		{
			return basicArr[costLevel][4];
		}
		else if(costType == FASTTOWER)
		{
			return fastArr[costLevel][4];
		}
		else if(costType == AOETOWER)
		{
			return areaOfEffectArr[costLevel][4];
		}
		else if(costType == HEAVYTOWER)
		{
			return heavyArr[costLevel][4];
		}
		else if(costType == MINETOWER)
		{
			return mineArr[costLevel][4];
		}
	}
	return 0;
}