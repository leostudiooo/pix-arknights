#include "CostIndicator.h"
#include "Combat.h"

CostIndicator::CostIndicator(const double startupCost, const double returnRate, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game), currCost(startupCost), returnRate(returnRate)
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
	currCost += returnRate;
	if (currCost < 0)
		currCost = 0;
	if (currCost > 99)
		currCost = 99;
	indicatorText.setString("Cost " + std::to_string(int(floor(currCost))));
}

void CostIndicator::render(sf::RenderWindow &window)
{
	window.draw(indicatorBackground);
	window.draw(indicatorText);
}

void CostIndicator::handleCombatEvent(const CombatEvent &event)
{
	// switch (event.getType())
	// {
	// 	case CombatEventType::OPERATOR_DEPLOY:
	// 	{
	// 		currCost -= event.getOperator()->getCost();
	// 		break;
	// 	}
	// 	case CombatEventType::ENEMY_DEATH:
	// 	{
	// 		currCost += event.getEnemy()->getReward();
	// 		break;
	// 	}
	// }
}