#include "CombatProgress.h"

#include "Combat.h"
#include "CombatEvent.h"

CombatProgress::CombatProgress(unsigned int totalEnemies, unsigned int defendPointLife, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game), totalEnemies(totalEnemies), defendPointLife(defendPointLife)
{
	progressBackground.setSize(sf::Vector2f(72, 10));
	progressBackground.setFillColor(sf::Color(0x22222299));
	progressBackground.setPosition(position);

	progressText.setFont(*game->getFont("font_small"));
	progressText.setCharacterSize(8);
	progressText.setFillColor(sf::Color(0xbbbbbbff));
	progressText.setPosition(position + sf::Vector2f(2, 0));

	defendPointLifeText.setFont(*game->getFont("font_small"));
	defendPointLifeText.setCharacterSize(8);
	defendPointLifeText.setFillColor(sf::Color(0xbbbbbbff));
	defendPointLifeText.setPosition(position + sf::Vector2f(50, 0));
}

void CombatProgress::handleEvent(const sf::Event &event)
{
}

void CombatProgress::update()
{
	progressText.setString("Enemy " + std::to_string(killCount) + "/" + std::to_string(totalEnemies));
	defendPointLifeText.setString("HP " + std::to_string(defendPointLife));
}

void CombatProgress::render(sf::RenderWindow &window)
{
	window.draw(progressBackground);
	window.draw(progressText);
	window.draw(defendPointLifeText);
	window.draw(killCountText);
}

void CombatProgress::handleCombatEvent(const CombatEvent &event)
{
}