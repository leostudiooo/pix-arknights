// Game.h
#pragma once

#include "AssetType.h"
#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <stack>
#include <memory>
#include <filesystem>

// forward declarations
class UserInterface;

class Game : public std::enable_shared_from_this<Game>
{
private:
	sf::RenderWindow window;
	sf::View view;

	std::string ASSET_PREFIX;
	std::stack<std::shared_ptr<UserInterface>> uiStack;

public:
	AssetManager assetManager;

	std::shared_ptr<Game> getGame() { return shared_from_this(); }
	std::shared_ptr<sf::Music> bgMusic;

	Game();
	~Game();

	void setAssetPrefix(const std::string &prefix) { ASSET_PREFIX = prefix; }

	void updateView();
	sf::Vector2f getMousePosition();

	void pushState(std::shared_ptr<UserInterface> ui, bool switchMusic = false);
	void pushStateHalfTransition(std::shared_ptr<UserInterface> ui, bool switchMusic = false);
	bool popState(bool switchMusic = false);
	bool popStateNoTransition();
	bool popStateHalfTransition(bool switchMusic = false);
	void setBgMusic(std::shared_ptr<sf::Music> music) { bgMusic = music; }

	void init();
	void run();
	void handleEvent();

	const std::string getAssetPrefix() const { return ASSET_PREFIX; }

	void loadSingleAsset(const AssetType assetType, const std::string &name, const std::string &filename);

	// shorthand for loadSingleAsset, prepends ASSET_PREFIX to filename
	void load(const AssetType type, const std::string &name, const std::string &filename) { loadSingleAsset(type, name, ASSET_PREFIX + filename); }

	std::shared_ptr<sf::Texture> getTexture(const std::string &name) { return assetManager.getTexture(name); }
	std::shared_ptr<sf::Music> getMusic(const std::string &name) { return assetManager.getMusic(name); }
	std::shared_ptr<sf::Font> getFont(const std::string &name) { return assetManager.getFont(name); }
};
