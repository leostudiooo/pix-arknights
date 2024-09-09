// Combat.h
#include "UserInterface.h"


#include "Operator.h"
#include "Enemy.h"
#include "CombatEvent.h"

#include "json.hpp"

#include <queue>

// Forward declaration
class CombatComponent;

class Combat : public UserInterface, public std::enable_shared_from_this<Combat>
{
protected:
	sf::Sprite background;
	std::vector<std::shared_ptr<CombatComponent> > components;
	std::queue<CombatEvent> eventQueue;

	std::string combatName;
	nlohmann::json combatData;

	std::vector<std::shared_ptr<Operator> > operators;
	std::vector<std::shared_ptr<Enemy> > enemies;
public:
	Combat() = default;
	Combat(std::shared_ptr<Game> game, std::string combatName);
	
	void loadAssets();
	
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;

	void createEvent(CombatEvent event) { eventQueue.push(event); }

	std::shared_ptr<Combat> getCombat() { return shared_from_this(); }
};