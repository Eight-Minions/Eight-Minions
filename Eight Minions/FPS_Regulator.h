#ifndef FPS_REG_H
#define FPS_REG_H
#include "resources.h"

class FPS_Regulator
{
private:
	int ticks;
	int FPS;
public:
	FPS_Regulator(int nFPS);

	void start();
	void killTime();

};



#endif