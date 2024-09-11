// Combat.h
#pragma once

#include "UserInterface.h"

#include "Operator.h"
#include "Enemy.h"
#include "CombatEvent.h"

#include "json.hpp"

#include <queue>

// Forward declaration
class CombatComponent;

enum CombatStatus
{
	INIT,
	NORMAL,
	PREDEPLOY,
	PREDEPLOY_SELECT_DIRECTION
};

class Combat : public UserInterface, public std::enable_shared_from_this<Combat>
{
protected:
	sf::Sprite background;
	std::vector<std::shared_ptr<CombatComponent> > components;

	std::queue<std::shared_ptr<CombatEvent> > eventQueue;
	CombatStatus status = INIT;

	std::string combatName;
	nlohmann::json combatData;

	double currCost;
	double returnRate;

	unsigned int frameCounter = 0;

	std::queue <nlohmann::json> enemyQueue;

public:
	Combat() = default;
	Combat(std::shared_ptr<Game> game, std::string combatName);

	void loadAssets();
	void initComponents();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void playMusic() override;

	CombatStatus getCombatStatus() const { return status; }

	double getCurrCost() const { return currCost; }
	void setCurrCost(double cost) { currCost = cost; }

	void createEvent(const std::shared_ptr<CombatEvent> event) { eventQueue.push(event); }
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event);
};
