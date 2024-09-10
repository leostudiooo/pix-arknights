// Combat.h
#include "UserInterface.h"

#include "Operator.h"
#include "Enemy.h"
#include "CombatEvent.h"

#include "json.hpp"

#include <queue>

// Forward declaration
class CombatComponent;

enum CombatStatus
{
	NORMAL,
	PREDEPLOY
};

class Combat : public UserInterface, public std::enable_shared_from_this<Combat>
{
protected:
	sf::Sprite background;
	std::vector<std::shared_ptr<CombatComponent>> components;

	std::queue<CombatEvent> eventQueue;
	CombatStatus status = NORMAL;

	std::string combatName;
	nlohmann::json combatData;

	std::vector<std::shared_ptr<Operator> > operators;
	std::vector<std::shared_ptr<Enemy> > enemies;

public:
	Combat() = default;
	Combat(std::shared_ptr<Game> game, std::string combatName);

	void loadAssets();
	void initComponents();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void playMusic() override;

	CombatStatus getCombatStatus() const { return status; }

	void createEvent(const CombatEvent &event) { eventQueue.push(event); }
	void handleCombatEvent(const CombatEvent &event);
};
