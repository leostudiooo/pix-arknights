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
    for (auto row : mapTiles)
    {
        int posX = origin.x;
        std::vector<std::shared_ptr<Tile>> tileRow;
        for (auto tile : row)
        {
            sf::Vector2f position = sf::Vector2f(posX, posY);
            int tileType = tile;
            tileRow.push_back(std::make_shared<Tile>(tileType, position, game->getTexture(tileTextures[tileType])));
            posX += 16;
        }
        tiles.push_back(tileRow);
        posY += 16;
    }
}

void CombatMap::loadAssets()
{
    for (auto tileTexture : tileTextures)
    {
        game->load(TEXTURE, tileTexture, "tiles/" + tileTexture + ".png");
    }
}

void CombatMap::handleEvent(const sf::Event &event)
{
}

void CombatMap::update()
{
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

void CombatMap::handleCombatEvent(const CombatEvent &event)
{
}