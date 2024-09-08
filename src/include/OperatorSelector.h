// OperatorSelector.h
#pragma once

#include "Operator.h"
#include "CombatComponent.h"

// Forward declaration
class Combat;

class OperatorSelector: public CombatComponent
{
protected:
	std::vector<sf::Sprite> selectorSprites;
public:
	OperatorSelector(std::shared_ptr<Combat> combat);
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(CombatEvent event) override;
};