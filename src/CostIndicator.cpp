#include "CostIndicator.h"
#include "Combat.h"

CostIndicator::CostIndicator(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game)
{
	indicatorBackground.setSize(sf::Vector2f(32, 9));
	indicatorBackground.setFillColor(sf::Color(0x22222299));
	indicatorBackground.setPosition(position);

	indicatorText.setFont(*game->getFont("font_small"));
	indicatorText.setCharacterSize(8);
	indicatorText.setFillColor(sf::Color(0xbbbbbbff));
	indicatorText.setPosition(position + sf::Vector2f(2, -1));
}

void CostIndicator::handleEvent(const sf::Event &event)
{
}

void CostIndicator::update()
{
	indicatorText.setString("Cost " + std::to_string(int(combat->getCurrCost())));
}

void CostIndicator::render(sf::RenderWindow &window)
{
	window.draw(indicatorBackground);
	window.draw(indicatorText);
}

void CostIndicator::handleCombatEvent(const std::shared_ptr<CombatEvent> event)
{
	// switch (event.getType())
	// {
	// 	case OPERATOR_DEPLOY:
	// 	{
	// 		currCost -= event.getOperator()->getCost();
	// 		break;
	// 	}
	// 	case ENEMY_DEATH:
	// 	{
	// 		currCost += event.getEnemy()->getReward();
	// 		break;
	// 	}
	// }
}