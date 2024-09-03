// Tile.h
#pragma once

#include "TileType.h"

#include <SFML/Graphics.hpp>

class Tile
{
private:
	TileType type;
	sf::Sprite tileSprite;
	bool isDeployable;
	
public:
	Tile() = default;

	// typeCode:
	// 0 - GROUND, deployable
	// 1 - GROUND, not deployable
	// 2 - HIGHLAND, deployable
	// 3 - HIGHLAND, not deployable
	// 4 - SPAWN_POINT, not deployable
	// 5 - DEFEND_POINT, not deployable
	Tile(int typeCode, sf::Texture& texture);
	
	TileType getType() const;
	sf::Sprite getTileSprite() const;
	bool getIsDeployable() const;
	
	void setType(TileType type);
	void setTileSprite(sf::Sprite tileSprite);
	void setIsDeployable(bool isDeployable);
	~Tile() = default;
};