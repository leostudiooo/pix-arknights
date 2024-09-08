// OperatorSelector.h
#pragma once

#include "Operator.h"
#include "CombatComponent.h"

// Forward declaration
class Combat;

class OperatorSelector: public CombatComponent
{
protected:
	std::shared_ptr<Combat> combat;
	std::vector<sf::Sprite> selectorSprites;
public:
	OperatorSelector() = default;
	OperatorSelector(std::shared_ptr<Combat> combat);

	void setCombat(std::shared_ptr<Combat> combat) { this->combat = combat; }

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(CombatEvent event) override;
};