// CombatProgress.h
#pragma once

#include "CombatComponent.h"

// Forward declaration
class Combat;
class CombatEvent;

class CombatProgress : public CombatComponent
{
protected:
	const sf::Vector2f position = sf::Vector2f(60, 0);
	sf::RectangleShape progressBackground;
	unsigned int killCount = 0, totalEnemies, defendPointLife;
	sf::Text progressText, killCountText, defendPointLifeText;

public:
	CombatProgress() = default;
	~CombatProgress() = default;

	CombatProgress(unsigned int totalEnemies, unsigned int defendPointLife, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game);

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const CombatEvent &event) override;

	void playMusic() override {} // useless feature
};