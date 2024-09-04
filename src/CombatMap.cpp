//CombatMap.cpp
#include "CombatMap.h"
#include "Tile.h"
#include "TileType.h"
#include "Game.h"
#include <fstream>

CombatMap::CombatMap(std::string mapFile, std::shared_ptr<Game> game) : UserInterface(game) {
    loadAssets();
    loadMap(mapFile);
}

void CombatMap::loadAssets() {
    // CHANGE: The following lines are commented out because the resources are loaded in the Game class.
    // Use game->load(Texture, "name", "path") to load the resources.

    // groundTexture.loadFromFile("ground.png");
    // groundUndeployableTexture.loadFromFile("ground_undeployable.png");
    // highlandTexture.loadFromFile("highland.png");
    // highlandUndeployableTexture.loadFromFile("highland_undeployable.png");
    // spawnPointTexture.loadFromFile("spawn_point.png");
    // defendPointTexture.loadFromFile("defend_point.png");
}

void CombatMap::loadMap(std::string mapFile) {
    std::ifstream file(mapFile);
    nlohmann::json jsonData;
    file >> jsonData;

    shape[0] = jsonData["tiles"].size(); // 高度
    shape[1] = jsonData["tiles"][0].size(); // 宽度

    tiles.resize(shape[0]);
    for (int i = 0; i < shape[0]; ++i) {
        tiles[i].resize(shape[1]);
        for (int j = 0; j < shape[1]; ++j) {
            int typeCode = jsonData["tiles"][i][j];

            auto texture = game->getTexture("ground");

            switch (typeCode) {
                case 0:
                    texture = game->getTexture("ground");
                    break;
                case 1:
                    texture = game->getTexture("ground_undeployable");
                    break;
                case 2:
                    texture = game->getTexture("highland");
                    break;
                case 3:
                    texture = game->getTexture("highland_undeployable");
                    break;
                case 4:
                    texture = game->getTexture("spawn_point");
                    break;
                case 5:
                    texture = game->getTexture("defend_point");
                    break;
                default:
                    break;
            }

            tiles[i][j] = Tile(typeCode, *texture);
        }
    }
}

void CombatMap::draw(sf::RenderWindow &window) {
    // for (int i = 0; i < shape[0]; ++i) {
    //     for (int j = 0; j < shape[1]; ++j) {
    //         sf::Vector2f position(static_cast<float>(j * 32), static_cast<float>(i * 32));
    //         tiles[i][j].getTileSprite().setPosition(position);
    //         window.draw(tiles[i][j].getTileSprite());
    //     }
    // }
}
