// Tile.h
#pragma once

#include "TileType.h"

#include <SFML/Graphics.hpp>
#include <memory>

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
	Tile(int typeCode, std::shared_ptr<sf::Texture> texture);
	
	TileType getType() const;
	sf::Sprite getTileSprite() const;
	bool getIsDeployable() const;

	void setPosition(float x, float y) { tileSprite.setPosition(x, y); }
	
	void setType(TileType type);
	void setTileSprite(sf::Sprite tileSprite);
	void setIsDeployable(bool isDeployable);

	void update() {}
	void handleEvent(const sf::Event &event) {}

	void render(sf::RenderWindow &window) const { window.draw(tileSprite); }
	~Tile() = default;
};