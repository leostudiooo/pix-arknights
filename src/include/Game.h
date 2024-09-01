// Game.h
#pragma once

#include "AssetManager.h"
#include "SplashScreen.h"
#include "GameState.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stack>
#include <memory>

class Game
{
private:
	const std::string ASSET_PREFIX = "../assets/";
	std::stack<GameState> stateStack;
	sf::RenderWindow window;
	AssetManager assetManager;
	std::unique_ptr<SplashScreen> splashScreen;

public:
	GameState currState;

	Game();
	~Game();

	void run();
	void handleEvent(const sf::Event &event);
	void update();
	void render();
	void handleInput();
	void loadAssets();
	void loadSingleAsset(const AssetType assetType, const std::string &name, const std::string &filename);
	void init();
};