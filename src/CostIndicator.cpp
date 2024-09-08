#include "CostIndicator.h"
#include "Combat.h"

CostIndicator::CostIndicator(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game)
{
	indicatorBackground.setSize(sf::Vector2f(32, 9));
	indicatorBackground.setFillColor(sf::Color(0x22222299));
	indicatorBackground.setPosition(position);

	indicatorText.setFont(* game->getFont("font_small"));
	indicatorText.setCharacterSize(8);
	indicatorText.setFillColor(sf::Color::White);
	indicatorText.setPosition(position + sf::Vector2f(2, 1));
}

void CostIndicator::handleEvent(const sf::Event &event)
{
}

void CostIndicator::update()
{
}

void CostIndicator::render(sf::RenderWindow &window)
{
	window.draw(indicatorBackground);
	window.draw(indicatorText);
}

void CostIndicator::handleCombatEvent(CombatEvent event)
{
}