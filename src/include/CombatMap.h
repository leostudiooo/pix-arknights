// CombatMap.h
#pragma once

#include "CombatComponent.h"

#include "json.hpp"
#include "Tile.h"
#include "Game.h"

#include <vector>


class CombatMap : public CombatComponent
{
protected:
	std::vector<std::vector<std::shared_ptr<Tile> > > tiles;
	nlohmann::json mapData;

public:
	CombatMap() = default;
	CombatMap(nlohmann::json mapData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void loadAssets();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(CombatEvent event) override;
};