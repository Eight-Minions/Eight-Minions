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
	if(ticks + (1000/FPS) < SDL_GetTicks())
		cout << "FPS DROP.\n";
	else
		SDL_Delay((1000/FPS) - (SDL_GetTicks() - ticks));
	//while(SDL_GetTicks() - ticks < (1000/FPS));
}
