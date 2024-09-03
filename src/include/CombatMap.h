// CombatMap.h
#pragma once

#include "Tile.h"

#include "json.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class CombatMap
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
	CombatMap(std::string mapFile);

	void loadAssets();
	void loadMap(std::string mapFile);
	void draw(sf::RenderWindow &window);
	
	~CombatMap() = default;
};