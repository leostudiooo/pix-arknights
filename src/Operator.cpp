#include "Operator.h"
#include "FigureLayer.h"
#include "Combat.h"

using json = nlohmann::json;

Operator::Operator(json opData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : Figure(combat, game, figureLayer)
{
	std::clog << opData << std::endl;
	name = opData["name"];
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

	position.x = tilePosition[0] * _tileSize + _tileOrigin.x + _globalDrawOffset.x;
	position.y = tilePosition[1] * _tileSize + _tileOrigin.y + _globalDrawOffset.y;

	healthBar.setPosition(position.x, position.y + _figHeight + 2);
	healthBar.setSize(sf::Vector2f(16, 1));
	healthBar.setFillColor(sf::Color(0xAADDFFFF));
	healthBar.setOutlineColor(sf::Color(0x222222FF));
	healthBar.setOutlineThickness(1);

	direction[0] = 1;
	direction[1] = 0;
}

void Operator::handleEvent(const sf::Event &event)
{
}

void Operator::update()
{
	frameCounter++;
	// Temporary attack animation
	// if (frameCounter % attackInterval == 0)
	// {
	// 	attackCounter++;
	// 	if (attackCounter % 2 == 0)
	// 	{
	// 		operatorSprite.setTexture(*operatorTextures[0]);
	// 	}
	// 	else
	// 	{
	// 		operatorSprite.setTexture(*operatorTextures[1]);
	// 	}
	// }
	if (currentHealth > 0)
	{
		if (currentHealth > maxHealth)
		{
			currentHealth = maxHealth;
		}
		healthBar.setSize(sf::Vector2f(16.0f * currentHealth / maxHealth, 1));
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
	window.draw(operatorSprite);
	window.draw(healthBar);
}

void Operator::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
}
