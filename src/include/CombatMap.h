// CombatMap.h
#pragma once

#include "UserInterface.h"

#include "json.hpp"
#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <vector>

class CombatMap : public UserInterface
{
private:
	int shape[2];
	std::vector<std::vector<Tile> > tiles;
	sf::Texture groundTexture;
	sf::Texture groundUndeployableTexture;
	sf::Texture highlandTexture;
	sf::Texture highlandUndeployableTexture;
	sf::Texture spawnPointTexture;
	sf::Texture defendPointTexture;

public:
	CombatMap() = default;
	CombatMap(std::string mapFile, std::shared_ptr<Game> game);

	void loadAssets();
	void loadMap(std::string mapFile);
	void handleEvent(const sf::Event &event) override { for (auto tileRow : tiles) for (auto tile : tileRow) tile.handleEvent(event); };
	void update() override { for (auto tileRow : tiles) for (auto tile : tileRow) tile.update(); };
	void render(sf::RenderWindow &window) override { for (auto tileRow : tiles) for (auto tile : tileRow) tile.render(window); };
	
	~CombatMap() = default;
};