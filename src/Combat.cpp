#include "Combat.h"

Combat::Combat(std::shared_ptr<Game> game, std::string mapName) : UserInterface(game)
{
	loadAssets();
}