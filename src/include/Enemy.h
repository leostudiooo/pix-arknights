// Enemy.h
#pragma once

#include "Figure.h"
#include "json.hpp"

enum EnemyType
{
	SLUG,
	SOLIDER,
	ARMED
};

enum EnemyStatus
{
	EN_ST_IDLE,
	EN_ST_MOVE,
	EN_ST_ATTACK
};

class Enemy: protected Figure
{
private:
	const EnemyType type;
	int moveSpeed; // in pixels per frame
	int collisionBox[4] = {8, 8, 0, 16}; // {right, left, bottom, top}, based on the bottom-center of the enemy sprite (16*16 px)

	int position[2];
	int direction[2];

	const int killReward = 3;

	EnemyStatus status;

	unsigned int frameCounter = 0;
	// Enemy image[3]: 32*32 px, status {regular, move, attack}

public:
	Enemy(nlohmann::json enemyData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer);
	~Enemy() = default;

	unsigned int getReward() const { return killReward; }

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event);
};