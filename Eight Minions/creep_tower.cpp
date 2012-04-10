#include "creep_tower.h"

Creep_Tower::Creep_Tower() : tower(){
}
Creep_Tower::Creep_Tower(int new_x, int new_y) : tower (CREEPTOWERSTARTLEVEL, -1, new_x, new_y){
}
Creep_Tower::Creep_Tower(int new_x, int new_y, game_host *nManager) : tower (CREEPTOWERSTARTLEVEL, -1, new_x, new_y){
	manager = nManager;
}
void Creep_Tower::unpause(){
	paused = false;
}
void Creep_Tower::pause(){
	paused = true;
}