//CombatMap.cpp
#include "CombatMap.h"
#include "CombatEvent.h"
#include "Tile.h"
#include "TileType.h"
#include "Game.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

CombatMap::CombatMap(nlohmann::json mapData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game), mapData(mapData)
{
    loadAssets();
}

void CombatMap::loadAssets()
{
    std::string tileTextures[] = {
        "defend_point",
        "ground",
        "ground_undeployable",
        "highland",
        "highland_undeployable",
        "spawn_point"
    };

    for (auto tileTexture: tileTextures)
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

void CombatMap::handleCombatEvent(CombatEvent event)
{
}