#include "standard_tower.h"

Standard_Tower::Standard_Tower() : tower()
{
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y) : tower(STANDARDTOWERSTARTLEVEL, p, t, set_x, set_y)
{
	changeType(t);
	attackTick = attackDuration;
	coolDownTick = coolDownDuration;
}
Standard_Tower::Standard_Tower(int l, int p, int t, int set_x, int set_y, game_host *nManager) : tower(STANDARDTOWERSTARTLEVEL, p, t, set_x, set_y)
{
	manager = nManager;
	changeType(t);
	attackTick = attackDuration;
	coolDownTick = coolDownDuration;
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
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((this->getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((cur->getData()->getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
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
		manager->sendMessageToQueue(UpdMess(this->getPlayer(), TOWERATTACK, this->getX(), this->getY(), closestCreep->getIndex(), this->attackType).getMT());
		chosenCreeps.push(closestCreep);
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
			double currentDistance = sqrt(pow((double)(((cur->getData()->getX() - BOARD_X_OFFSET)/GRID_SIZE)-((position.getX() - BOARD_X_OFFSET)/GRID_SIZE)), 2) +
				pow((double)(((position.getY() - BOARD_Y_OFFSET)/GRID_SIZE)-((this->getY() - BOARD_Y_OFFSET)/GRID_SIZE)), 2));
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
		manager->sendMessageToQueue(UpdMess(this->getPlayer(), TOWERATTACK, this->getX(), this->getY(), closestCreep->getIndex(), this->attackType).getMT());
		chosenCreeps.push(closestCreep);
	}
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
				manager->sendMessageToQueue(UpdMess(this->getPlayer(), TOWERATTACK, this->getX(), this->getY(), cur->getIndex(), this->attackType).getMT());
				chosenCreeps.push(cur);
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
				//Tower Attack:	UpdMess(Player[1], TOWERATTACK, AttackerX[2], AttackerY[2], AttackedID[4], AttackType[2]);
				manager->sendMessageToQueue(UpdMess(this->getPlayer(), TOWERATTACK, this->getX(), this->getY(), cur->getIndex(), this->attackType).getMT());
				chosenCreeps.push(cur);
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
	Retruns false if it needs to go to the next iteration
*/
bool Standard_Tower::doDamage()
{
	cListNode<creep*> *frontNode = NULL;
	creep *frontCreep = NULL;
	if(attackTick <= 0)
	{
		while(chosenCreeps.empty() == false)
		{
			frontNode = chosenCreeps.front();
			if(frontNode != NULL)// Does the creep still exist?
			{
				frontCreep = frontNode->getData();
				if(frontCreep != NULL)
				{
					if(frontCreep->isAlive() == true){
						frontCreep->damage(damageValue);
						manager->sendMessageToQueue(UpdMess(frontCreep->getPlayer(), CREEP, frontCreep->getX(), frontCreep->getY(), frontCreep->getHealth()).getMT());
						if(frontCreep->isAlive() == false)
						{
							manager->getPlayer(this->getPlayer())->addMoney(frontCreep->getReward());
							// Update money value for player based on reward for killing the creep
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
	if(getType() == BASICTOWER)
	{
		damageValue =			basicArr[getLevel() - 1][0];
		armorPenetration =		basicArr[getLevel() - 1][1];
		range =					basicArr[getLevel() - 1][2];
		coolDownDuration =		basicArr[getLevel() - 1][3];
		cost =					basicArr[getLevel() - 1][4];
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
		cost =					fastArr[getLevel() - 1][4];
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
		cost =					fastArr[getLevel() - 1][4];
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
		cost =					heavyArr[getLevel() - 1][4];
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
		cost =					mineArr[getLevel() - 1][4];
		attackDuration =		MINEATTACKDELAY;
		attackType =			AREAOFEFFECT;
		attackStrategy =		ATTACKCLOSESTTOTOWER;
	}
	else
		return false;
	return true;
}
void Standard_Tower::sell()
{
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