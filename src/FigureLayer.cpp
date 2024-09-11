#include "FigureLayer.h"

#include "Operator.h"
#include "Enemy.h"
#include "Combat.h"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

FigureLayer::FigureLayer(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game)
{
	loadAssets();
}

void FigureLayer::loadAssets()
{
	std::ifstream operatorFile(game->getAssetPrefix() + "operators/operators.json");
	operatorData = json::parse(operatorFile);
	operatorData = operatorData["operators"];
	operatorFile.close();
	for (auto &op : operatorData)
	{
		std::string opName = op["name"];
		game->load(TEXTURE, opName + "_idle", "operators/" + opName + "/idle.png");
		game->load(TEXTURE, opName + "_attack", "operators/" + opName + "/attack.png");
	}

	std::ifstream enemyFile(game->getAssetPrefix() + "enemies/enemies.json");
	enemyData = json::parse(enemyFile);
	enemyData = enemyData["enemies"];
	enemyFile.close();
	for (auto &en : enemyData)
	{
		std::string enName = en["name"];
		game->load(TEXTURE, enName + "_idle", "enemies/" + enName + "/idle.png");
		game->load(TEXTURE, enName + "_attack", "enemies/" + enName + "/attack.png");
	}

}

void FigureLayer::handleEvent(const sf::Event &event)
{
	for (auto &op : operators)
	{
		op->handleEvent(event);
	}
	for (auto &en : enemies)
	{
		en->handleEvent(event);
	}
}

void FigureLayer::update()
{
	for (auto &op : operators)
	{
		op->update();
	}
	for (auto &en : enemies)
	{
		en->update();
	}
}

void FigureLayer::render(sf::RenderWindow &window)
{
	for (auto &op : operators)
	{
		op->render(window);
	}
	for (auto &en : enemies)
	{
		en->render(window);
	}
}

void FigureLayer::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
	switch (event->getType())
	{
	case ENEMY_SPAWN:
	{
		auto enemy = std::make_shared<Enemy>(event->getData(), combat, game, shared_from_this());
		enemies.push_back(enemy);
		break;
	}
	case OPERATOR_DEPLOY:
	{
		auto operatorData = event->getData();
		std::string opName = operatorData["name"];
		auto op = std::make_shared<Operator>(operatorData, combat, game, shared_from_this());
		operators.push_back(op);
		break;
	}
	default:
		break;
	}
}