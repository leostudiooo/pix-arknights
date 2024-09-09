#include "Combat.h"
#include "CombatComponent.h"
#include "CombatEvent.h"
#include "OperatorSelector.h"

OperatorSelector::OperatorSelector(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game) : CombatComponent(combat, game)
{
}

void OperatorSelector::handleEvent(const sf::Event &event)
{
}

void OperatorSelector::update()
{
}

void OperatorSelector::render(sf::RenderWindow &window)
{
}

void OperatorSelector::handleCombatEvent(const CombatEvent &event)
{
}