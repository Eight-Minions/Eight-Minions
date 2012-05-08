#ifndef EMENEMY_H
#define EMENEMY_H
#include "client.h"

class client;

class EMenemy
{
public:
	EMenemy(client *pass, int nDiff);

	int iterate();
private:
	int level;
	int difficulty;

	client *game;
};

#endif