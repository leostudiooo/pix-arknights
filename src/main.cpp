#include "Game.h"

int main()
{
	auto game = std::make_shared<Game>();
	game->run();
	game->init();
}