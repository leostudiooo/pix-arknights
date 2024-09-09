#include "Tile.h"

Tile::Tile(int typeCode, sf::Vector2f position, sf::Texture texture)
{
	type = static_cast<TileType>(typeCode);
	tileSprite.setPosition(position);
	tileSprite.setTexture(texture);
	visualOverlay.setPosition(position);
	visualOverlay.setSize(sf::Vector2f(16,16));
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
	window.draw(visualOverlay);
}