#include "Combat.h"
#include "CombatComponent.h"
#include "CombatMap.h"
#include "CostIndicator.h"
#include "OperatorSelector.h"

#include <fstream>

using json = nlohmann::json;

Combat::Combat(std::shared_ptr<Game> game, std::string combatName) : UserInterface(game), combatFileName(combatFileName)
{
	loadAssets();

	background.setTexture(* game->getTexture("combat_bg_img"));
	background.setPosition(0, 0);

	components.push_back(std::make_shared<CombatMap>(combatData["combatMap"], getCombat(), game));

	game->bgMusic = game->getMusic("combat_bg_music");
}

void Combat::loadAssets()
{
	std::ifstream file(game->getAssetPrefix() + "levels/" + combatFileName + ".json");
	combatData = json::parse(file);

	game->load(MUSIC, "combat_bg_music", "combat/combat.mp3");
	game->load(TEXTURE, "combat_bg_img", "combat/bg.png");
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
	window.draw(background);
	for(auto component : components)
	{
		component->render(window);
	}
}