// CombatMap.cpp
#include "CombatMap.h"

#include "Combat.h"
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
    for (auto row : tiles)
    {
        for (auto tile : row)
        {
            tile->setMousePos(game->getMousePosition());
            tile->handleEvent(event);
        }
    }
}

void CombatMap::update()
{
    for (auto row : tiles)
    {
        for (auto tile : row)
        {
            tile->update();
            if (tile->getTriggered())
            {
                std::clog << "Tile at " << tile->getTileX() << ", " << tile->getTileY() << " is triggered" << std::endl;
                tile->setTriggered(false);
                if (combat->getCombatStatus() == PREDEPLOY && isDeployable(currentOperator["type"], tile))
                {
                    json eventData;
                    eventData = currentOperator;
                    eventData["tilePosition"] = {tile->getTileX(), tile->getTileY()};
                    eventData["direction"] = {1, 0};
                    combat->createEvent(std::make_shared<CombatEvent>(OPERATOR_DEPLOY, eventData));
                    std::clog << "Create deploy event of operator " << currentOperator["name"] << " at " << tile->getTileX() << ", " << tile->getTileY() << std::endl;
                }
            }
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
    switch (event->getType())
    {
    case OPERATOR_PREDEPLOY:
    {
        json eventData = event->getData();
        currentOperator = eventData;
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
        break;
    }
    case OPERATOR_CANCEL_PREDEPLOY:
    {
        for (auto row : tiles)
            for (auto tile : row)
                tile->setOverlay(NONE);
        currentOperator.clear();
        break;
    }
    case OPERATOR_SELECT_DIRECTION:
    {
        break;
    }
    case OPERATOR_DEPLOY:
    {
        for (auto row : tiles)
            for (auto tile : row)
                tile->setOverlay(NONE);
        currentOperator = event->getData();
        auto tile = getTileAt(currentOperator["tilePosition"][0], currentOperator["tilePosition"][1]);
        tile->setOccupied(true);
        currentOperator.clear();
        break;
    }
    default:
        break;
    }
}
