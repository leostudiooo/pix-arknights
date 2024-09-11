#include "Enemy.h"
#include "FigureLayer.h"

using json = nlohmann::json;

Enemy::Enemy(json enemyData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : Figure(combat, game, figureLayer)
{
	name = enemyData["name"];
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

	auto spawnPt = route.front();
	position.x = spawnPt[0] * _tileSize + _tileOrigin.x + _globalDrawOffset.x - _figHeight;
	position.y = spawnPt[1] * _tileSize + _tileOrigin.y + _globalDrawOffset.y - _figHeight;
}

void Enemy::handleEvent(const sf::Event &event)
{
}

void Enemy::update()
{
	frameCounter++;
}

void Enemy::render(sf::RenderWindow &window)
{
	enemySprite.setPosition(position);
	window.draw(enemySprite);
}

void Enemy::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
}