#include "mine.h"

Mine::Mine() : Standard_Tower()
{
}
Mine::Mine(int level, int player, int type, int set_x, int set_y) : Standard_Tower(level, player, type, set_x, set_y)
{
}
Mine::Mine(int level, int player, int type, int set_x, int set_y, game_host *nManager) : Standard_Tower(level, player, type, set_x, set_y, nManager)
{
}
Mine::~Mine()
{
}