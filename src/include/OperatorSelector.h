// OperatorSelector.h
#pragma once

#include "Operator.h"
#include "CombatComponent.h"

#include "json.hpp"

// Forward declaration
class CombatEvent;
class OperatorSelectorBlock;

class OperatorSelector: public CombatComponent
{
protected:
	sf::RectangleShape bgBar;
	std::vector<std::shared_ptr<OperatorSelectorBlock> > selectorBlocks;
	const std::string opBranchStr[4] = { "D", "G", "M", "S" };
	nlohmann::json operatorData;
	
public:
	OperatorSelector() = default;
	OperatorSelector(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void setCombat(std::shared_ptr<Combat> combat) { this->combat = combat; }

	void loadAssets();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const CombatEvent &event) override;
	void playMusic() override {}; // Useless for combat components
};