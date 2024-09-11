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
	operatorDatabase = json::parse(operatorFile);
	operatorDatabase = operatorDatabase["operators"];
	operatorFile.close();
	for (auto &op : operatorDatabase)
	{
		std::string opName = op["name"];
		game->load(TEXTURE, opName + "_idle", "operators/" + opName + "/idle.png");
		game->load(TEXTURE, opName + "_attack", "operators/" + opName + "/attack.png");
	}

	std::ifstream enemyFile(game->getAssetPrefix() + "enemies/enemies.json");
	enemyDatabase = json::parse(enemyFile);
	enemyDatabase = enemyDatabase["enemies"];
	enemyFile.close();
	for (auto &en : enemyDatabase)
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
        int enType = event->getData()["enemyType"];
        auto enemyData = enemyDatabase[enType];
		enemyData["route"] = event->getData()["route"];
		std::clog << "Enemy " << enemyCount << " spawned" << std::endl;
		auto enemy = std::make_shared<Enemy>(enemyData, combat, game, shared_from_this());
		enemies.push_back(enemy);
		enemyCount++;
		break;
	}
	case OPERATOR_DEPLOY:
	{
		std::string operatorName = event->getData()["name"];
		json operatorData = std::find_if(operatorDatabase.begin(), operatorDatabase.end(), [operatorName](json &op) { return op["name"] == operatorName; }).value();
        operatorData["tilePosition"] = event->getData()["tilePosition"];
		auto op = std::make_shared<Operator>(operatorData, combat, game, shared_from_this());
		operators.push_back(op);
		break;
	}
	default:
		break;
	}
}
