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
    sf::Vector2f position = origin;
    for (auto row : mapTiles)
    {
        std::vector<std::shared_ptr<Tile>> tileRow;
        for (auto tile : row)
        {
            int tileType = tile;
            tileRow.push_back(std::make_shared<Tile>(tileType, position, *game->getTexture(tileTextures[tileType])));
            position += sf::Vector2f(16, 0);
        }
        tiles.push_back(tileRow);
        position += sf::Vector2f(0, 16);
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