#include "Operator.h"
#include "FigureLayer.h"
#include "Combat.h"

using json = nlohmann::json;

Operator::Operator(json opData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : Figure(combat, game, figureLayer)
{
	std::clog << opData << std::endl;
	name = opData["name"];
	id = opData["id"];
	maxHealth = opData["maxHealth"];
	currentHealth = maxHealth;
	attackDamage = opData["attackDamage"];
	attackInterval = opData["attackInterval"];
	defenseAmount = opData["defenseAmount"];

	int typeInt = opData["type"];
	type = static_cast<OperatorType>(typeInt);

	int branchInt = opData["branch"];
	branch = static_cast<OperatorBranch>(branchInt);

	blockNumber = opData["blockNumber"];

	for (auto &row : opData["attackRange"])
	{
		std::vector<bool> rowVector;
		for (auto &cell : row)
		{
			int cellBool = cell;
			rowVector.push_back(bool(cellBool));
		}
		attackRange.push_back(rowVector);
	}

	attackRangeOffset.push_back(opData["attackRangeOffset"][0]);
	attackRangeOffset.push_back(opData["attackRangeOffset"][1]);

	tilePosition.push_back(opData["tilePosition"][0]);
	tilePosition.push_back(opData["tilePosition"][1]);

	operatorTextures.push_back(game->getTexture(name + "_idle"));
	operatorTextures.push_back(game->getTexture(name + "_attack"));
	operatorSprite.setTexture(*operatorTextures[0]);

	position = tileToWorld(tilePosition);

	healthBar.setPosition(position.x, position.y + _figHeight + 2);
	healthBar.setSize(sf::Vector2f(16, 1));
	healthBar.setFillColor(sf::Color(0xAADDFFFF));
	healthBar.setOutlineColor(sf::Color(0x222222FF));
	healthBar.setOutlineThickness(1);

	direction[0] = 1;
	direction[1] = 0;

	setAttackRangeRects();
	collisionBox = sf::FloatRect(position.x - 0.1f * _figHeight, position.y - 0.1f * _figHeight, _figHeight * 1.2, _figHeight * 1.2);

	// Medic is always in attack status
	if (branch == MEDIC)
		status = OP_ST_ATTACK;

	attackRangeVisible = true;
}

void Operator::removeInRangeEnemy(int id)
{
	auto it = std::find_if(inRangeEnemies.begin(), inRangeEnemies.end(), [id](const std::shared_ptr<Enemy> &enemy)
						   { return enemy && enemy->getId() == id; });
	if (it != inRangeEnemies.end())
	{
		inRangeEnemies.erase(it);
	}
}

void Operator::setAttackRangeRects()
{
	attackRangeRects.clear();
	for (int i = 0; i < attackRange.size(); i++)
	{
		for (int j = 0; j < attackRange[i].size(); j++)
		{
			if (attackRange[i][j])
			{
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(_tileSize, _tileSize));
				rect.setPosition(position.x + (j - attackRangeOffset[0]) * _tileSize, position.y + (i - attackRangeOffset[1]) * _tileSize);
				rect.setFillColor(sf::Color(0xffdd44bb));
				attackRangeRects.push_back(rect);
			}
		}
	}
}

bool Operator::isInRange(const sf::Vector2f pos) const
{
	for (auto &rect : attackRangeRects)
		if (rect.getGlobalBounds().contains(pos))
			return true;
	return false;
}

void Operator::attemptAttack()
{
	if (status == OP_ST_ATTACK || status == OP_ST_BLOCKING)
	{
		if (attackCounter % attackInterval == 0)
		{
			attackCounter = 0;
			if (branch != MEDIC)
			{
				if (inRangeEnemies.size() > 0)
				{
					inRangeEnemies[0]->getHit(attackDamage);
					std::clog << "Operator " << name << " attack enemy " << inRangeEnemies[0]->getId() << std::endl;
				}
			}
			else // Medic send a heal event
			{
				auto e = std::make_shared<CombatEvent>(OPERATOR_HEAL);
				json data;
				data["healAmount"] = attackDamage;
				e->setData(data);
				combat->createEvent(e);
				std::clog << "Medic heal" << std::endl;
			}
		}
		attackCounter++;
	}
}

void Operator::handleEvent(const sf::Event &event)
{
	// if (event.type == sf::Event::MouseMoved)
	// {
	// 	if (figureSprite.getGlobalBounds().contains(game->getMousePosition()))
	// 		attackRangeVisible = true;
	// 	else
	// 		attackRangeVisible = false;
	// }
}

void Operator::update()
{
	frameCounter++;
	if (frameCounter > 3 * 60)
		attackRangeVisible = false;
	if (currentHealth > 0)
	{
		currentHealth = std::min(maxHealth, currentHealth);
		healthBar.setSize(sf::Vector2f(16.0f * currentHealth / maxHealth, 1));

		// Remove nullptr from inRangeEnemies
		inRangeEnemies.erase(
			std::remove_if(inRangeEnemies.begin(), inRangeEnemies.end(), [](const std::shared_ptr<Enemy> &enemy)
						   { return !enemy; }),
			inRangeEnemies.end());

		// Search or block enemies in range
		if (inRangeEnemies.size() > 0)
		{
			status = OP_ST_ATTACK;
			for (auto &enemy : inRangeEnemies)
			{
				if (enemy && collisionBox.contains(enemy->getCenterPosition()))
				{
					currentBlockingNumber = 0;
					if (currentBlockingNumber < blockNumber && type == MELEE)
					{
						status = OP_ST_BLOCKING;
						currentBlockingNumber++;
						auto e = std::make_shared<CombatEvent>(OPERATOR_BLOCKING_ENEMY);
						json data;
						data["operatorId"] = getId();
						data["enemyId"] = enemy->getId();
						e->setData(data);
						combat->createEvent(e);
						// std::clog << "Operator " << name << " blocking enemy " << enemy->getId() << std::endl;
					}
				}
				else
					break;
			}
		}
		else if (branch != MEDIC) // Medic is always in attack status
		{
			status = OP_ST_IDLE;
			attackCounter = -1;
		}
		attemptAttack();
	}
	else
	{
		json eventData;
		eventData["id"] = id;
		combat->createEvent(std::make_shared<CombatEvent>(OPERATOR_DEATH, eventData));
		}
}

void Operator::render(sf::RenderWindow &window)
{
	operatorSprite.setPosition(position);
	if (attackRangeVisible)
		for (auto &attackRangeRect : attackRangeRects)
			window.draw(attackRangeRect);
	if (attackCounter <= attackInterval / 2 && attackCounter >= 0)
		operatorSprite.setTexture(*operatorTextures[1]); // attack texture
	else
		operatorSprite.setTexture(*operatorTextures[0]); // idle texture
	window.draw(operatorSprite);
	window.draw(healthBar);
}

void Operator::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
	switch (event->getType())
	{
	case OPERATOR_HEAL:
	{
		auto data = event->getData();
		int healAmount = data["healAmount"];
		currentHealth = std::min(maxHealth, currentHealth + healAmount);
		break;
	}
	case ENEMY_MOVE:
	{
		if (branch == MEDIC)
			break;
		auto data = event->getData();
		int enemyId = data["id"];
		auto enemyPos = data["center"];
		if (isInRange(sf::Vector2f(enemyPos[0], enemyPos[1])))
		{
			auto enemy = figureLayer->getEnemyById(enemyId);
			if (enemy)
				if (std::find(inRangeEnemies.begin(), inRangeEnemies.end(), enemy) == inRangeEnemies.end())
					addInRangeEnemy(enemy);
		}
		else
			removeInRangeEnemy(enemyId);
		break;
	}
	case ENEMY_DEATH:
	{
		auto data = event->getData();
		auto enemyId = data["id"];
		removeInRangeEnemy(enemyId);
		break;
	}
	case ENEMY_REACH_GOAL:
	{
		auto data = event->getData();
		auto enemyId = data["id"];
		removeInRangeEnemy(enemyId);
		break;
	}
	default:
		break;
	}
}
