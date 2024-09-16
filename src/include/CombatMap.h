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

	const std::string tileTextures[6] = {
        "ground",
        "ground_undeployable",
        "highland",
        "highland_undeployable",
        "spawn_point",
        "defend_point"};
	
	nlohmann::json currentOperator;

public:
	CombatMap(nlohmann::json mapData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void loadAssets();

	bool isDeployable(unsigned int opType, std::shared_ptr<Tile> tile);
	bool isLegalTile(unsigned int x, unsigned int y) { return (x < tiles[0].size() && y < tiles.size()); }
	std::shared_ptr<Tile> getTileAt(unsigned int x, unsigned int y) { if (isLegalTile(x, y)) return tiles[y][x]; else return nullptr;}

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event) override;

	void playMusic() override {} // useless
};