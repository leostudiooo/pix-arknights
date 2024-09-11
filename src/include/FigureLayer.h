// FigureLayer.h
#pragma once

#include "CombatComponent.h"

#include "json.hpp"

// Forward declarations
class Operator;
class Enemy;

class FigureLayer : public CombatComponent
{
protected:
	std::vector<std::shared_ptr<Operator> > operators;
	std::vector<std::shared_ptr<Enemy> > enemies;
	nlohmann::json operatorData;
	nlohmann::json enemyData;
public:
	FigureLayer(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void addOperator(std::shared_ptr<Operator> op) { operators.push_back(op); }
	void addEnemy(std::shared_ptr<Enemy> en) { enemies.push_back(en); }

	void loadAssets();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event) override;

	void playMusic() override {} // useless
};