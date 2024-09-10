// CostIndicator.h
#pragma once

#include "CombatComponent.h"

class CostIndicator: public CombatComponent
{
protected:
	double currCost;
	double returnRate;
	sf::RectangleShape indicatorBackground;
	sf::Text indicatorText;
	sf::Vector2f position = sf::Vector2f(160, 81);
public:
	CostIndicator() = default;
	~CostIndicator() = default;

	CostIndicator(const double startupCost, const double returnRate, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void setCombat(std::shared_ptr<Combat> combat) { this->combat = combat; }

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const CombatEvent &event) override;

	void playMusic() override {} // useless feature
};