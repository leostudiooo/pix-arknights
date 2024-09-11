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

	if (type == GROUND || type == HIGHLAND)
		isDeployable = true;
	else
		isDeployable = false;

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
	if (isOccupied) isDeployable = false;
	else if (type == GROUND || type == HIGHLAND) isDeployable = true;
	switch(overlayType)
	{
		case NONE:
			visualOverlay.setFillColor(sf::Color(0x00000000));
			break;
		case PREVIEW_DEPLOYABLE:
			if(isDeployable) visualOverlay.setFillColor(sf::Color(0x57ff57bb));
			break;
		case PREVIEW_RANGE:
			visualOverlay.setFillColor(sf::Color(0xffab57bb));
			break;
	}
}

void Tile::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left && !isTriggered)
		{
			if (tileSprite.getGlobalBounds().contains(mousePos))
			{
				isTriggered = true;
			}
		}
	}
}

void Tile::render(sf::RenderWindow &window)
{
	window.draw(tileSprite);
	if(overlayType) window.draw(visualOverlay);
}