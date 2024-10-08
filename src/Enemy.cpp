#include "Enemy.h"
#include "Operator.h"
#include "Combat.h"
#include "FigureLayer.h"
#include "CombatEvent.h"

#include <iostream>

using json = nlohmann::json;

Enemy::Enemy(json enemyData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : Figure(combat, game, figureLayer)
{
	std::clog << enemyData << std::endl;
	name = enemyData["name"];
	id = enemyData["id"];
	maxHealth = enemyData["maxHealth"];
	currentHealth = maxHealth;
	attackDamage = enemyData["attackDamage"];
	attackInterval = enemyData["attackInterval"];
	defenseAmount = enemyData["defenseAmount"];

	int typeInt = enemyData["type"];
	type = static_cast<EnemyType>(typeInt);

	moveSpeed = enemyData["moveSpeed"];

	for (auto &pt : enemyData["route"])
	{
		std::vector<int> point;
		point.push_back(pt[0]);
		point.push_back(pt[1]);
		route.push(point);
	}

	enemyTextures[0] = game->getTexture(name + "_idle");
	enemyTextures[1] = game->getTexture(name + "_attack");
	enemySprite.setTexture(*enemyTextures[0]);

	healthBar.setSize(sf::Vector2f(16, 2));
	healthBar.setFillColor(sf::Color(0xFFDDAAFF));
	healthBar.setOutlineColor(sf::Color(0x222222FF));
	healthBar.setOutlineThickness(1);

	auto spawnPt = route.front();
	position = tileToWorld(spawnPt);
	nextTileAbsPos = position;
	route.pop();
}

void Enemy::attemptAttack()
{
	if (blockingOp)
	{
		if (attackCounter % attackInterval == 0)
		{
			attackCounter = 0;
			blockingOp->getHit(attackDamage);
		}
		attackCounter++;
	}
}

void Enemy::handleEvent(const sf::Event &event)
{
}

void Enemy::update()
{
	frameCounter++;
	if (currentHealth > 0)
	{
		currentHealth = std::min(currentHealth, maxHealth);
		healthBar.setSize(sf::Vector2f(16.0f * currentHealth / maxHealth, 1));

		if (currBlockingOpId >= 0)
			status = EN_ST_BLOCKED;
		else
		{
			attackCounter = -1;
			status = EN_ST_MOVE;
		}

		switch (status)
		{
		case EN_ST_MOVE:
		{
			updatePosition();
			enemySprite.setPosition(position);
			healthBar.setPosition(position.x, position.y + _figHeight + 1);
			break;
		}
		case EN_ST_BLOCKED:
		{
			attemptAttack();
			break;
		}
		default:
			attackCounter = 0;
			break;
		}
		auto e = std::make_shared<CombatEvent>(ENEMY_MOVE);
		json data;
		data["id"] = id;
		data["position"] = {position.x, position.y};
		data["center"] = {position.x + 0.5 * _figHeight, position.y + 0.5 * _figHeight};
		e->setData(data);
		combat->createEvent(e);
	}
	else
	{
		json eventData;
		eventData["id"] = id;
		eventData["reward"] = killReward;
		combat->createEvent(std::make_shared<CombatEvent>(ENEMY_DEATH, eventData));
	}
}

void Enemy::render(sf::RenderWindow &window)
{
	enemySprite.setPosition(position);
	if (attackCounter <= attackInterval / 2 && attackCounter >= 0)
		enemySprite.setTexture(*enemyTextures[1]);
	else
		enemySprite.setTexture(*enemyTextures[0]);
	window.draw(enemySprite);
	if (currentHealth < maxHealth)
		window.draw(healthBar);
}

void Enemy::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
	switch (event->getType())
	{
	case OPERATOR_BLOCKING_ENEMY:
	{
		json data = event->getData();
		int enemyId = data["enemyId"];
		if (enemyId == id)
		{
			currBlockingOpId = event->getData()["operatorId"];
			blockingOp = figureLayer->getOperatorById(currBlockingOpId);
			status = EN_ST_BLOCKED;
			blockingLock = true;
			// std::clog << "Enemy " << id << " blocked by operator " << currBlockingOpId << std::endl;
		}
		break;
	}
	case OPERATOR_DEATH:
	case OPERATOR_RETREAT:
	{
		int eventOpId = event->getData()["id"];
		std::clog << "Operator " << eventOpId << " died or retreated" << std::endl;
		std::clog << "Enemy " << id << " current blocking operator id: " << currBlockingOpId << std::endl;
		if (eventOpId == currBlockingOpId)
		{
			std::clog << "Enemy " << id << " is no longer blocked" << std::endl;
			currBlockingOpId = -1;
			blockingOp = nullptr;
			blockingLock = false;
		}
		status = EN_ST_MOVE;
	}
	default:
	{
		status = EN_ST_MOVE;
		break;
	}
	}
}

void Enemy::updatePosition()
{
	// 检查是否已经到达当前目标点
	if (std::abs(position.x - nextTileAbsPos.x) < moveSpeed &&
		std::abs(position.y - nextTileAbsPos.y) < moveSpeed)
	{
		// 如果到达当前目标点，切换到下一个路径点
		if (!route.empty())
		{
			auto nextTile = route.front();
			route.pop();
			nextTileAbsPos = tileToWorld(nextTile);
		}
		else
		{
			json data;
			data["reward"] = killReward;
			data["id"] = id;
			combat->createEvent(std::make_shared<CombatEvent>(ENEMY_REACH_GOAL, data));
			return;
		}
	}

	// 计算下一帧的位置 (基于方向和速度)
	sf::Vector2f direction = nextTileAbsPos - position;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f normalizedDir = direction / length;

	// 更新当前位置
	position += sf::Vector2f(normalizedDir.x * moveSpeed, normalizedDir.y * moveSpeed);
}