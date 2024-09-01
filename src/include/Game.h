// Game.h
#pragma once

#include "AssetType.h"
#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <stack>
#include <memory>

// forward declarations
class UserInterface;

class Game: public std::enable_shared_from_this<Game>
{
private:
	sf::RenderWindow window;
	sf::View view;

	const std::string ASSET_PREFIX = "../assets/";
	AssetManager assetManager;
	std::stack<std::unique_ptr<UserInterface> > uiStack;

	std::shared_ptr<Game> sharedThis() { return shared_from_this(); }

public:
	Game();
	~Game();

	void pushState(std::unique_ptr<UserInterface> ui);
	void popState();

	void run();
	void handleEvent();
	void handleInput();
	void loadAssets();
	void loadSingleAsset(const AssetType assetType, const std::string &name, const std::string &filename);
	void init();
};