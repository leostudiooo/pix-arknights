#include "Combat.h"
#include "CombatComponent.h"

#include "CombatProgress.h"
#include "CombatMap.h"
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

	int startupCost = combatData["cost"]["startup"];
	currCost = startupCost;
	returnRate = combatData["cost"]["returnRate"];
	components.push_back(std::make_shared<CostIndicator>(shared_from_this(), game));

	components.push_back(std::make_shared<CombatProgress>(11, 3, shared_from_this(), game));

	components.push_back(std::make_shared<OperatorSelector>(shared_from_this(), game));
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
	if (event->getType() == CombatEventType::OPERATOR_PREDEPLOY)
		status = PREDEPLOY;
	else if (event->getType() == CombatEventType::OPERATOR_SELECT_DIRECTION)
		status = PREDEPLOY_SELECT_DIRECTION;
	else if (event->getType() == CombatEventType::OPERATOR_DEPLOY ||CombatEventType::OPERATOR_CANCEL_PREDEPLOY)
		status = NORMAL;
}