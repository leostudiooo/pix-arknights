// Enemy.h
#pragma once

#include "Figure.h"
#include "json.hpp"

#include <queue>

enum EnemyType
{
	SLUG,
	SOLIDER,
	ARMED
};

// Status machine
enum EnemyStatus
{
	EN_ST_IDLE,
	EN_ST_MOVE,
	EN_ST_BLOCKED,
	EN_ST_ATTACK
};

// Forward declaration
class Operator;

class Enemy: protected Figure
{
private:
	EnemyType type;
	float moveSpeed; // in pixels per frame
	int collisionBox[4] = {8, 8, 0, 16}; // {right, left, bottom, top}, based on the bottom-center of the enemy sprite (16*16 px)

	sf::Vector2f position;

	const int killReward = 3;

	EnemyStatus status = EN_ST_MOVE;

	unsigned int frameCounter = 0;
    unsigned int attackCounter = 0;
	// Enemy image[3]: 32*32 px, status {move, attack}
	std::shared_ptr<sf::Texture> enemyTextures[2];
	sf::Sprite enemySprite;

    std::queue<std::vector<int> > route; // route to follow, in tile coordinates

	sf::Vector2f currFrmPos;
	sf::Vector2f nextFrmPos;
	sf::Vector2f nextTileAbsPos;

	std::shared_ptr<Operator> blockingOp;
public:
	Enemy(nlohmann::json enemyData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer);
	~Enemy() = default;

	unsigned int getReward() const { return killReward; }
	int getId() const { return id; }
	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getCenterPosition() const { return position + sf::Vector2f(0.5f * _figHeight, 0.5f * _figHeight); }

	void getHit(int damage) { currentHealth = safeSubtract(currentHealth, std::max(int(std::ceil(0.05 * damage)), damage - defenseAmount)); }
	void attemptAttack();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event);

	void updatePosition();
};
