// Combat.h
#include "UserInterface.h"
#include "CombatMap.h"
#include "CombatComponent.h"
#include "CostIndicator.h"
#include "Button.h"
#include "Operator.h"
#include "OperatorSelector.h"
#include "Enemy.h"
#include "CombatEvent.h"

#include <queue>

class Combat : public UserInterface, public std::enable_shared_from_this<Combat>
{
protected:
	sf::Sprite background;
	CombatMap combatMap;

	OperatorSelector operatorSelector;
	std::queue<CombatEvent> eventQueue;
	std::vector<std::shared_ptr<Operator> > operators;
	std::vector<std::shared_ptr<Enemy> > enemies;
public:
	Combat() = default;
	Combat(std::shared_ptr<Game>, std::string);
	void loadAssets();
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	std::shared_ptr<Combat> getCombat() { return shared_from_this(); }
};