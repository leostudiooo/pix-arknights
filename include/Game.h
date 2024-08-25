// Game.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>

enum GameState
{
	SPLASH_SCREEN,
	MAIN_MENU,
	TERMINAL,
	SQUAD,
	OPERATOR,
	ARCHIVE,
	COMBAT,
	SETTLEMENT
};

class Game
{
private:
	GameState currState;
	std::stack<GameState> stateStack;

public:
	Game(/* args */);
	~Game();
};