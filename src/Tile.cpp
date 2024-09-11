#include "Tile.h"

#include <iostream>

Tile::Tile(int typeCode, sf::Vector2f position, std::shared_ptr<sf::Texture> texture, unsigned int x, unsigned int y) : x(x), y(y)
{
	type = static_cast<TileType>(typeCode);
	tileSprite.setPosition(position);
	tileSprite.setTexture(*texture);
	visualOverlay.setPosition(position + sf::Vector2f(2, 2));
	visualOverlay.setSize(sf::Vector2f(12, 12));
	visualOverlay.setFillColor(sf::Color(0x00000000));

	std::clog << "Tile type " << type << " created at " << position.x << ", " << position.y << " by " << x << ", " << y << std::endl;
}

TileType Tile::getType() const
{
	return type;
}

bool Tile::getIsDeployable() const
{
	return isDeployable;
}

void Tile::setIsDeployable(bool isDeployable)
{
	this->isDeployable = isDeployable;
}

void Tile::setOverlay(OverlayType overlayType)
{
	this->overlayType = overlayType;
}

void Tile::update()
{
	switch(overlayType)
	{
		case NONE:
			visualOverlay.setFillColor(sf::Color(0x00000000));
			break;
		case PREVIEW_DEPLOYABLE:
			visualOverlay.setFillColor(sf::Color(0x57ff57bb));
			break;
		case PREVIEW_RANGE:
			visualOverlay.setFillColor(sf::Color(0xffab57bb));
			break;
	}
}

void Tile::handleEvent(const sf::Event &event)
{
}

void Tile::render(sf::RenderWindow &window)
{
	window.draw(tileSprite);
	if(overlayType) window.draw(visualOverlay);
}