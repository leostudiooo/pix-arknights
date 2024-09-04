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
    for (const auto& level : levels) {
        std::string mapFile = level["map"];
    void CombatMap::loadAssets(const std::string& mapFile) {
    // 从 mapFile 中提取关卡的名称
    std::string levelName = mapFile.substr(0, mapFile.find(".json"));

    // 定义地块的文件名格式
    std::unordered_map<std::string, std::string> tileTextures = {
        {"Ground", "combat_map/ground.png"},
        {"Ground_undeployable", "combat_map/ground_undeployable.png"},
        {"Highland", "combat_map/highland.png"},
        {"Highland_undeployable", "combat_map/highland_undeployable.png"},
        {"Spawn_point", "combat_map/spawn_point.png"},
        {"Defend_point", "combat_map/defend_point.png"}
    };
    

    // 循环加载所有地块的纹理
    for (const auto& [tileType, textureFile] : tileTextures) {
        std::string fullPath = "combat_map/" + textureFile;
        game->load(TEXTURE, levelName + "_" + tileType, fullPath);
    }
    // 使用提取的关卡名称生成音乐的文件名
        std::string musicFile = "combat_map/" + levelName + ".mp3";

        // 加载对应的音乐
        load(MUSIC, levelName + "_music", musicFile);
}
CombatMap combatMap(mapFile);
}
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
                    texture = game->getTexture("Ground");
                    break;
                case 1:
                    texture = game->getTexture("Ground_undeployable");
                    break;
                case 2:
                    texture = game->getTexture("Highland");
                    break;
                case 3:
                    texture = game->getTexture("Highland_undeployable");
                    break;
                case 4:
                    texture = game->getTexture("Spawn_point");
                    break;
                case 5:
                    texture = game->getTexture("Defend_point");
                    break;
                default:
                    break;
            }

            tiles[i][j] = Tile(typeCode, *texture);
        }
    }
}