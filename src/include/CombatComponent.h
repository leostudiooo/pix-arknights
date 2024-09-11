// CombatComponent.h
#pragma once

#include "UserInterface.h"

#include <memory>

// Forward declarations
class Combat;
class CombatEvent;

class CombatComponent : public UserInterface
{
protected:
	std::shared_ptr<Combat> combat;

public:
	CombatComponent(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : combat(combat), UserInterface(game) {}

	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void handleCombatEvent(const std::shared_ptr<CombatEvent> event) = 0;

	void setCombat(std::shared_ptr<Combat> combat) { this->combat = combat; }
};
