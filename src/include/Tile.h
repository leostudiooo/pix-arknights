// Tile.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

enum TileType
{
	GROUND, // MELEE
	GROUND_UNDEPLOYABLE,
	HIGHLAND, // RANGED
	HIGHLAND_UNDEPLOYABLE,
	SPAWN_POINT,
	DEFEND_POINT
};

enum OverlayType
{
	NONE,
	PREVIEW_DEPLOYABLE,
	PREVIEW_RANGE
};

class Tile
{
private:
	TileType type;
	OverlayType overlayType = NONE;

	sf::Sprite tileSprite;
	sf::RectangleShape visualOverlay;

	bool isDeployable = false;
	bool isOccupied = false;
	bool isTriggered = false;

	unsigned int x, y;

	sf::Vector2f mousePos;

public:
	Tile() = default;

	// typeCode:
	// 0 - GROUND, deployable
	// 1 - GROUND, not deployable
	// 2 - HIGHLAND, deployable
	// 3 - HIGHLAND, not deployable
	// 4 - SPAWN_POINT, not deployable
	// 5 - DEFEND_POINT, not deployable
	Tile(int typeCode, sf::Vector2f position, std::shared_ptr<sf::Texture> texture, unsigned int x, unsigned int y);

	TileType getType() const;

	bool getIsDeployable() const;
	void setIsDeployable(bool isDeployable);

	void setMousePos(sf::Vector2f mousePos) { this->mousePos = mousePos; }

	bool getTriggered() const { return isTriggered; }
	void setTriggered(bool isTriggered) { this->isTriggered = isTriggered; }

	OverlayType getOverlay() const { return overlayType; }
	void setOverlay(OverlayType overlayType);

	bool getOccupied() const { return isOccupied; }
	void setOccupied(bool isOccupied) { this->isOccupied = isOccupied; }

	std::vector<unsigned int> getTilePosition() const { return {x, y}; }
	unsigned int getTileX() const { return x; }
	unsigned int getTileY() const { return y; }

	void update();
	void handleEvent(const sf::Event &event);
	void render(sf::RenderWindow &window);
	void render(sf::RenderWindow &window) const { window.draw(tileSprite); }

	~Tile() = default;
};