#include "FPS_Regulator.h"

FPS_Regulator::FPS_Regulator( int nFPS )
{
	FPS = nFPS;
	ticks = 0;
}

void FPS_Regulator::start()
{
	ticks = SDL_GetTicks();
}

void FPS_Regulator::killTime()
{
	while(SDL_GetTicks() - ticks > FPS);
}
