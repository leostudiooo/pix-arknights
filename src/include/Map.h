// Map.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum TileType {
    EMPTY,            // 空
    MELEE_DEPLOYABLE, // 近战可部署
    RANGED_DEPLOYABLE,// 远程可部署
    SPAWN_POINT,      // 红门
    DEFENSE_POINT,    // 蓝门
    PATH              // 敌人行进路径，同时也是近战可部
};


class Tile {
private:
    TileType type;
    sf::Sprite tileSprite;
    bool canDeployOperator;

public:
    Tile(int tileCode, const sf::Texture& texture) {
    switch(tileCode) {
        case 0:
            type = EMPTY;
            canDeployOperator = false;
            break;
        case 1:
            type = MELEE_DEPLOYABLE;
            canDeployOperator = true;
            break;
        case 2:
            type = RANGED_DEPLOYABLE;
            canDeployOperator = true;
            break;
        case 3:
            type = SPAWN_POINT;
            canDeployOperator = false;
            break;
        case 4:
            type = DEFENSE_POINT;
            canDeployOperator = false;
            break;
        case 5:
            type = PATH;
            canDeployOperator = true; // PATH 同时也是近战可部署地块
            break;
        default:
            type = EMPTY; // 默认情况下设置为 EMPTY
            canDeployOperator = false;
            break;
    }
    tileSprite.setTexture(texture);
}


    TileType getType() const {
        return type;
    }

    bool isDeployable() const {
        return canDeployOperator;
    }

    void draw(sf::RenderWindow &window, const sf::Vector2f &position) {
        tileSprite.setPosition(position);
        window.draw(tileSprite);
    }
};

class Map {
private:
    static const int WIDTH = 10; // 地图宽度（像素点）
    static const int HEIGHT = 5; // 地图高度（像素点）
    Tile* tiles[HEIGHT][WIDTH];
    sf::Vector2i spawnPoint;
    sf::Vector2i defensePoint;
    sf::Texture texture; // 将 texture 定义为 Map 类的成员

public:
    Map(const std::string& filename, const sf::Texture& texture) : texture(texture) {
        loadFromFile(filename, texture);
    }

    ~Map() {
        // 清理 Tile 对象
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                delete tiles[y][x];
            }
        }
    }

    void loadFromFile(const std::string& filename, const sf::Texture& texture);//地块文件读取

    void draw(sf::RenderWindow &window);//位置计算及渲染

    sf::Vector2i getSpawnPoint() const {
        return spawnPoint;
    }

    sf::Vector2i getDefensePoint() const {
        return defensePoint;
    }

    std::vector<sf::Vector2i> getEnemyPath(); // 获取敌人行进路径
};


void Map::loadFromFile(const std::string& filename, const sf::Texture& texture) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open map file " << filename << std::endl;
        return;
    }

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int tileCode;
            if (!(file >> tileCode)) {
                std::cerr << "Error: Incorrect map format in file " << filename << std::endl;
                return;
            }

            // 根据地块代码创建 Tile 对象并存入 tiles 数组
            tiles[y][x] = new Tile(tileCode, texture);
            if (tileCode == 2) {
                spawnPoint = sf::Vector2i(x, y);
            } else if (tileCode == 3) {
                defensePoint = sf::Vector2i(x, y);
            }
        }
    }

    file.close();
}

void Map::draw(sf::RenderWindow &window) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (tiles[y][x]) {
                sf::Vector2f position(static_cast<float>(x * texture.getSize().x),
                                      static_cast<float>(y * texture.getSize().y));
                tiles[y][x]->draw(window, position);
            }
        }
    }
}
