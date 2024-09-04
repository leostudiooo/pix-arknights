#include "Tile.h"

Tile::Tile(int typeCode, std::shared_ptr<sf::Texture> texture)
{
	switch (typeCode) {
		case 0:
			type = TileType::GROUND;
			isDeployable = true;
			break;
		case 1:
			type = TileType::GROUND;
			isDeployable = false;
			break;
		case 2:
			type = TileType::HIGHLAND;
			isDeployable = true;
			break;
		case 3:
			type = TileType::HIGHLAND;
			isDeployable = false;
			break;
		case 4:
			type = TileType::SPAWN_POINT;
			isDeployable = false;
			break;
		case 5:
			type = TileType::DEFEND_POINT;
			isDeployable = false;
			break;
		default:
			type = TileType::GROUND;
			isDeployable = true;
			break;
	}

	tileSprite.setTexture(*texture);
}

TileType Tile::getType() const
{}

sf::Sprite Tile::getTileSprite() const
{}

bool Tile::getIsDeployable() const
{}

void Tile::setType(TileType type)
{}

void Tile::setTileSprite(sf::Sprite tileSprite)
{}

void Tile::setIsDeployable(bool isDeployable) 
{}