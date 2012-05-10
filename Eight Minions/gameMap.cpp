#include "gameMap.h"

gameMap::gameMap()
{


	//set the location of each players bases, these are used as goals for the creeps pathfinding
	Bases[0].x = PLAYERONEX;
	Bases[0].y = PLAYERONEY;
	Bases[1].x = PLAYERTWOX;
	Bases[1].y = PLAYERTWOY;
}

bool gameMap::isEmptyLocation(int xLoc, int yLoc)
{
	cListNode<creep*> *curCreepNode = creepList.getStart();
	if(xLoc >= MAPSIZE_X || xLoc < 0 || yLoc >= MAPSIZE_Y || yLoc < 0)
		return false;
	if(Tmap[xLoc][yLoc] != NULL)
		return false;
	while(curCreepNode != NULL)
	{
		if(xLoc == curCreepNode->getData()->p.getNext().x && yLoc == curCreepNode->getData()->p.getNext().y)
			return false;
		if(xLoc == curCreepNode->getData()->getPrev().x && yLoc == curCreepNode->getData()->getPrev().y)
			return false;
		curCreepNode = curCreepNode->getNext();
	}
	return true;
}

int gameMap::placeTower(int playerNumber, int towerType, int x, int y)
{
	int newTowerID = 0;
	if(Tmap[x][y] == NULL)
	{
		if(towerType == STRUCTURE)
		{
			if(Tmap[x][y] == NULL)
			{
				if(2 <= p[playerNumber - 1]->getMoney())
				{
					Nodemap[x][y] = true;
					if(!pathTestCreep->p.genPath(Nodemap, false))
					{
						Nodemap[x][y] = false;
						return 0;
					}
					structure *newStructure = new structure(STRUCTURESTARTLEVEL, playerNumber, towerType, x, y);
					p[playerNumber - 1]->spendMoney(2);
					newTowerID = this->towerList.insertInOrder(newStructure);
					Tmap[x][y] = newStructure;
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else if(towerType >= NORMTOWER && towerType <= HEAVYTOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Standard_Tower *newTower = new Standard_Tower(STANDARDTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= p[playerNumber - 1]->getMoney())
				{
					p[playerNumber - 1]->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else
					return 0;
			}
			else return 0;
		}
		else if(towerType == MINETOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Mine *newTower = new Mine(MINETOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= p[playerNumber - 1]->getMoney())
				{
					p[playerNumber - 1]->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else
					return 0;
			}
			else return 0;
		}
		else if(towerType == OBSTACLE)
		{
			if(Tmap[x][y] == NULL)
			{
				Obstacle *newTower = new Obstacle(OBSTACLE, x, y);
				newTowerID = this->towerList.insertInOrder(newTower);
				Tmap[x][y] = newTower;
			}
			else
				return 0;
		}
		else if(towerType >= NORMCREEPTOWER && towerType <= FATTYCREEPTOWER)
		{
			if(Tmap[x][y] == NULL)
			{
				Creep_Tower *newTower = new Creep_Tower(CREEPTOWERSTARTLEVEL, playerNumber, towerType, x, y, this);
				if(newTower->getCost() <= p[playerNumber - 1]->getMoney())
				{
					int newCost = newTower->getCost();
					p[playerNumber - 1]->spendMoney(newTower->getCost());
					newTowerID = this->towerList.insertInOrder(newTower);
					Tmap[x][y] = newTower;
				}
				else 
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
		updatePaths(x,y);
		return 1;
	}
	else
		return 0;
}

bool gameMap::changeStructure(int structureID, int newType)
{
	int setX = 0;
	int setY = 0;
	int playerNumber = 0;
	int cost = 0;
	if(towerList.checkForObjectWithID(structureID))
	{
		if(towerList.getNodeWithID(structureID)->getData()->getType() == STRUCTURE)
		{
			// Set values
			setX = towerList.getNodeWithID(structureID)->getData()->getX();
			setY = towerList.getNodeWithID(structureID)->getData()->getY();
			playerNumber = towerList.getNodeWithID(structureID)->getData()->getPlayer();
			switch(newType)
			{
			case NORMTOWER:
				cost = basicArr[0][4];
				break;
			case FASTTOWER:
				cost = fastArr[0][4];
				break;
			case AOETOWER:
				cost = areaOfEffectArr[0][4];
				break;
			case HEAVYTOWER:
				cost = heavyArr[0][4];
				break;
			case NORMCREEPTOWER:
				cost = normCreepArr[0][4] * 20;
				break;
			default:
				cout << "tower type not added...";
			}
			// Remove the old tower
			if(p[playerNumber - 1]->getMoney() >= cost)
			{
				removeTowerLocal(structureID);
				return placeTowerForced(playerNumber, newType, setX, setY, structureID);
			}
		}
	}
	return false;
}

void gameMap::updatePaths(int newX, int newY)
{
	cout << "updating paths";
	bool doRecalc = false;
	int i;
	int len;
	creep *temp;
	for (cListNode<creep*> *cur = creepList.getStart(); cur != NULL; cur = cur->getNext())
	{
		cout << ".";
		temp = cur->getData();
		len = temp->p.fPath.size();
		for(i = 0; i < len && !doRecalc; i++)
		{
			if(temp->p.fPath[i].x == newX && temp->p.fPath[i].y == newY)
				doRecalc = true;
		}
		if(doRecalc)
			temp->recalcPath(Nodemap);		
	}
	cout << "done!\n";
}

player * gameMap::getPlayer( int pnum )
{
	return p[pnum - 1];
}

cList<creep*> * gameMap::getCreepList()
{
	return &creepList;
}
