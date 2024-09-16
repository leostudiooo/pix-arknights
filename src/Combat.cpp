#include "Combat.h"
#include "CombatComponent.h"

#include "CombatProgress.h"
#include "CombatMap.h"
#include "FigureLayer.h"
#include "CostIndicator.h"
#include "OperatorSelector.h"

#include <fstream>
#include <memory>

using json = nlohmann::json;

Combat::Combat(std::shared_ptr<Game> game, std::string combatName) : UserInterface(game), combatName(combatName)
{
	loadAssets();

	background.setTexture(*game->getTexture("combat_bg_img"));
	background.setPosition(0, 0);
}

void Combat::initComponents()
{
	components.push_back(std::make_shared<CombatMap>(combatData["combatMap"], shared_from_this(), game));

	components.push_back(std::make_shared<FigureLayer>(shared_from_this(), game));

	int startupCost = combatData["cost"]["startup"];
	currCost = startupCost;
	returnRate = combatData["cost"]["returnRate"];
	components.push_back(std::make_shared<CostIndicator>(shared_from_this(), game));

	int totalEnemies = 0;
	int spawnFrame = 0;
	for (auto &fragment : combatData["enemies"]["fragments"])
	{
		for (auto &enemy : fragment["actions"])
		{
			totalEnemies++;
			unsigned int delay = enemy["delay"];
			spawnFrame += delay;
			json enemyData = enemy;
			enemyData["route"] = fragment["route"];
			enemyData["spawnFrame"] = spawnFrame;
			enemyQueue.push(enemyData);
		}
	}
	int defendPointLife = combatData["defendPointLife"];
	components.push_back(std::make_shared<CombatProgress>(totalEnemies, defendPointLife, shared_from_this(), game));

	components.push_back(std::make_shared<OperatorSelector>(shared_from_this(), game));

	status = NORMAL;
	frameCounter = 0;
}

void Combat::loadAssets()
{
	std::clog << "Loading combat " << game->getAssetPrefix() + "levels/" + combatName + ".json" << std::endl;
	std::ifstream file(game->getAssetPrefix() + "levels/" + combatName + ".json");

	try
	{
		combatData = json::parse(file);
		std::clog << combatData << std::endl;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error loading combat " << combatName << std::endl;
	}

	game->load(MUSIC, "combat_bg_music", "combat/combat.mp3");
	game->load(TEXTURE, "combat_bg_img", "combat/bg.png");

	file.close();
}

void Combat::handleEvent(const sf::Event &event)
{
	for (auto component : components)
	{
		component->handleEvent(event);
	}
}

void Combat::update()
{
	switch (status)
	{
	case NORMAL:
	{
		frameCounter++;
		if (!enemyQueue.empty())
		{
			auto enemy = enemyQueue.front();
			if (frameCounter == enemy["spawnFrame"])
			{
				enemyQueue.pop();
				createEvent(std::make_shared<CombatEvent>(ENEMY_SPAWN, enemy));
			}
		}

		currCost += returnRate;
		if (currCost < 0)
			currCost = 0;
		if (currCost > 99)
			currCost = 99;

		while (!eventQueue.empty())
		{
			auto event = eventQueue.front();
			eventQueue.pop();
			handleCombatEvent(event);
			for (auto component : components)
			{
				component->handleCombatEvent(event);
			}
		}
		for (auto component : components)
		{
			component->update();
		}
		break;
	}
	case SWITCH_TO_SETTLEMENT:
	{
		unsigned int rating;
		if (missionFailed) rating = 0;
		else
		{
			rating = 3;
			if (!perfectConduction) rating--;
			if (!noDeath) rating--;
		}
		// switching to settlement
		break;
	}
	default:
	{
		break;
	}
	}
}

void Combat::render(sf::RenderWindow &window)
{
	window.draw(background);
	for (auto component : components)
	{
		component->render(window);
	}
}

void Combat::playMusic()
{
	if (game->bgMusic)
		game->bgMusic->stop();
	game->bgMusic = game->getMusic("combat_bg_music");
	game->bgMusic->setLoop(true);
	game->bgMusic->play();
	std::clog << "Playing combat music" << std::endl;
}

void Combat::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
	switch (event->getType())
	{
	case OPERATOR_PREDEPLOY:
	{
		status = PREDEPLOY;
		std::clog << "Combat received predeploy event" << std::endl;
		break;
	}
	case OPERATOR_SELECT_DIRECTION:
	{
		status = PREDEPLOY_SELECT_DIRECTION;
		break;
	}
	case OPERATOR_CANCEL_PREDEPLOY:
	{
		status = NORMAL;
		std::clog << "Combat received cancel predeploy event" << std::endl;
		break;
	}
	case OPERATOR_DEPLOY:
	{
		status = NORMAL;
		unsigned int opCost = event->getData()["cost"];
		currCost -= opCost;
		break;
	}
	case OPERATOR_DEATH:
	{
		noDeath = false;
		break;
	}
	case ENEMY_DEATH:
	{
		int reward = event->getData()["reward"];
		currCost += reward;
		break;
	}
	case ENEMY_REACH_GOAL:
	{
		perfectConduction = false;
		break;
	}
	case MISSION_FAILED:
	{
		status = SWITCH_TO_SETTLEMENT;
		missionFailed = true;
		break;
	}
	case MISSION_ACCOMPLISHED:
	{
		status = SWITCH_TO_SETTLEMENT;
		break;
	}
	default:
		break;
	}
}