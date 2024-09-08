#include "Combat.h"
#include "CombatComponent.h"

#include <fstream>

using json = nlohmann::json;

Combat::Combat(std::shared_ptr<Game> game, std::string combatName) : UserInterface(game), combatFileName(combatFileName)
{
	loadAssets();

	game->bgMusic = game->getMusic("combat");
}

void Combat::loadAssets()
{
	std::ifstream file(game->getAssetPrefix() + "levels/" + combatFileName + ".json");
	combatData = json::parse(file);

	game->load(MUSIC, "combat", "combat/combat.mp3");
}

void Combat::handleEvent(const sf::Event &event)
{
	for(auto component : components)
	{
		component->handleEvent(event);
	}
}

void Combat::update()
{
	while(!eventQueue.empty())
	{
		auto event = eventQueue.front();
		eventQueue.pop();

		for(auto component : components)
		{
			component->handleCombatEvent(event);
		}
	}
	for(auto component : components)
	{
		component->update();
	}
}

void Combat::render(sf::RenderWindow &window)
{
	for(auto component : components)
	{
		component->render(window);
	}
}