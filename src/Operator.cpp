#include "Operator.h"
#include "FigureLayer.h"

using json = nlohmann::json;

Operator::Operator(json opData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : Figure(combat, game, figureLayer)
{
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
			rowVector.push_back(cell);
		}
		attackRange.push_back(rowVector);
	}

	attackRangeOffset.push_back(opData["attackRangeOffset"][0]);
	attackRangeOffset.push_back(opData["attackRangeOffset"][1]);

	tilePosition.push_back(opData["tilePosition"][0]);
	tilePosition.push_back(opData["tilePosition"][1]);

	operatorTextures[0] = game->getTexture(name + "_idle");
	operatorTextures[1] = game->getTexture(name + "_attack");
	operatorSprite.setTexture(*operatorTextures[0]);

	const sf::Vector2f _tileOrigin = {24, 16};
	const int _tileSize = 16;
	position.x = tilePosition[0] * _tileSize + _tileOrigin.x + _globalDrawOffset.x;
	position.y = tilePosition[1] * _tileSize + _tileOrigin.y + _globalDrawOffset.y;

	direction[0] = 1;
	direction[1] = 0;
}

void Operator::handleEvent(const sf::Event &event)
{
}

void Operator::update()
{
	frameCounter++;
	if (frameCounter % attackInterval == 0)
	{
		attackCounter++;
		if (attackCounter % 2 == 0)
		{
			operatorSprite.setTexture(*operatorTextures[0]);
		}
		else
		{
			operatorSprite.setTexture(*operatorTextures[1]);
		}
	}
}

void Operator::render(sf::RenderWindow &window)
{
	operatorSprite.setPosition(position);
	window.draw(operatorSprite);
}

void Operator::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
}