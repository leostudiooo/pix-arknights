//CombatMap.cpp
#include "CombatMap.h"
#include <fstream>

CombatMap::CombatMap(std::string mapFile) {
    loadAssets();
    loadMap(mapFile);
}

void CombatMap::loadAssets() {
    groundTexture.loadFromFile("ground.png");
    groundUndeployableTexture.loadFromFile("ground_undeployable.png");
    highlandTexture.loadFromFile("highland.png");
    highlandUndeployableTexture.loadFromFile("highland_undeployable.png");
    spawnPointTexture.loadFromFile("spawn_point.png");
    defendPointTexture.loadFromFile("defend_point.png");
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
            sf::Texture* texture = nullptr;

            switch (typeCode) {
                case 0:
                    texture = &groundTexture;
                    break;
                case 1:
                    texture = &groundUndeployableTexture;
                    break;
                case 2:
                    texture = &highlandTexture;
                    break;
                case 3:
                    texture = &highlandUndeployableTexture;
                    break;
                case 4:
                    texture = &spawnPointTexture;
                    break;
                case 5:
                    texture = &defendPointTexture;
                    break;
                default:
                    texture = &groundTexture;
                    break;
            }

            tiles[i][j] = Tile(typeCode, *texture);
        }
    }
}

void CombatMap::draw(sf::RenderWindow &window) {
    for (int i = 0; i < shape[0]; ++i) {
        for (int j = 0; j < shape[1]; ++j) {
            sf::Vector2f position(static_cast<float>(j * 32), static_cast<float>(i * 32)); // 假设每个 tile 是 32x32 像素
            tiles[i][j].getTileSprite().setPosition(position);
            window.draw(tiles[i][j].getTileSprite());
        }
    }
}
