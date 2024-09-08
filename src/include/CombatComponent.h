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
	CombatComponent() = default;
	CombatComponent(std::shared_ptr<Combat> combat) : combat(combat) {}
	virtual ~CombatComponent() = default;

	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void handleCombatEvent(CombatEvent event) = 0;
};