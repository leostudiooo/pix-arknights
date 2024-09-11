// CombatMap.cpp
#include "CombatMap.h"

#include "CombatEvent.h"
#include "Tile.h"

#include "Game.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

// Forward declaration
class Combat;

CombatMap::CombatMap(nlohmann::json mapData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game), mapData(mapData)
{
    loadAssets();

    auto mapSize = mapData["size"];
    auto mapTiles = mapData["tiles"];

    sf::Vector2f origin = sf::Vector2f(24, 16);
    int posY = origin.y;
    int tileY = 0;
    for (auto row : mapTiles)
    {
        int posX = origin.x;
        int tileX = 0;
        std::vector<std::shared_ptr<Tile>> tileRow;
        for (auto tile : row)
        {
            sf::Vector2f position = sf::Vector2f(posX, posY);
            int tileType = tile;
            tileRow.push_back(std::make_shared<Tile>(tileType, position, game->getTexture(tileTextures[tileType]), tileX, tileY));
            posX += 16;
            tileX++;
        }
        tiles.push_back(tileRow);
        posY += 16;
        tileY++;
    }
}

void CombatMap::loadAssets()
{
    for (auto tileTexture : tileTextures)
    {
        game->load(TEXTURE, tileTexture, "tiles/" + tileTexture + ".png");
    }
}

bool CombatMap::isDeployable(unsigned int opType, std::shared_ptr<Tile> tile)
{
    if (opType == 0 && tile->getType() == 0)
        return true;
    else if (opType == 1 && tile->getType() == 2)
        return true;
    else
        return false;
}

void CombatMap::handleEvent(const sf::Event &event)
{
}

void CombatMap::update()
{
    for (auto row : tiles)
    {
        for (auto tile : row)
        {
            tile->update();
        }
    }
}

void CombatMap::render(sf::RenderWindow &window)
{
    for (auto row : tiles)
    {
        for (auto tile : row)
        {
            tile->render(window);
        }
    }
}

void CombatMap::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
    if (event->getType() == OPERATOR_PREDEPLOY)
    {
        json eventData = event->getData();
        unsigned int opType = eventData["type"];
        std::clog << "CombatMap received predeploy event, opType " << opType << std::endl;
        for (auto row : tiles)
        {
            for (auto tile : row)
            {
                if (isDeployable(opType, tile))
                {
                    tile->setOverlay(PREVIEW_DEPLOYABLE);
                    std::clog << "Tile at " << tile->getTileX() << ", " << tile->getTileY() << " is deployable" << std::endl;
                }
            }
        }
    }
    else if (event->getType() == OPERATOR_CANCEL_PREDEPLOY)
    {
        for (auto row : tiles)
        {
            for (auto tile : row)
            {
                tile->setOverlay(NONE);
            }
        }
    }
}