// Operator.h
#pragma once

#include "Figure.h"
#include "json.hpp"

/*
 * `OperatorType` is an enumeration type that represents the type of the Operator.
 * It can be either `MELEE` or `RANGED`.
 *
 * In json type code:
 * - 0: melee
 * - 1: ranged
 */
enum OperatorType
{
	MELEE,
	RANGED
};

/*
 * `OperatorBranch` is an enumeration type that represents the branch of the Operator.
 * It can be `DEFENDER`, `GUARD`, `MEDIC`, or `SNIPER`.
 *
 * In json branch code:
 * - 0: defender
 * - 1: guard
 * - 2: medic
 * - 3: sniper
 */
enum OperatorBranch
{
	DEFENDER,
	GUARD,
	MEDIC,
	SNIPER
};

// Status machine
enum OperatorStatus
{
	OP_ST_IDLE,
	OP_ST_BLOCKING,
	OP_ST_ATTACK
};

// Forward declaration
class Enemy;

class Operator : protected Figure
{
private:
	OperatorType type;
	OperatorBranch branch;
	unsigned int blockNumber;
	int currentBlockingNumber = 0;

	/*
	 * `attackRange` is a 2D-array that represents the attack range of the Operator, based on the Operator's own frame (facing right).
	 * e.g. a typical sniper has an attack range of
	 * [ [1, 1, 1, 0],
	 * ..[1, 1, 1, 1],
	 * ..[1, 1, 1, 0] ]
	 * and a typical guard has an attack range of
	 * [[1, 1]]
	 */
	std::vector<std::vector<bool>> attackRange;

	/*
	 * `attackRangeOffset` is a 2D-array that represents the position of the operator in the attack range.
	 * e.g. a typical sniper has an attack range offset of
	 * [0, 1]
	 * which means the sniper is standing at '*' in the following attack range:
	 * [ [1, 1, 1, 0],
	 * ..[*, 1, 1, 1],
	 * ..[1, 1, 1, 0] ]
	 */
	std::vector<int> attackRangeOffset;

	/*
	 * `direction` is an 2D-array that represents the direction of the Operator, based on the game frame.
	 * Game frame:
	 * → y, ↓ x
	 * - [0, 1] -> right
	 * - [0, -1] -> left
	 * - [1, 0] -> down
	 * - [-1, 0] -> up
	 */
	std::vector<int> direction = {1, 0}; // right

	std::vector<int> tilePosition;

	unsigned int frameCounter = 0;
	unsigned int attackCounter = 0;

	// Operator image[2]: 32*32 px, status {idle, attack}
	std::vector<std::shared_ptr<sf::Texture>> operatorTextures;
	sf::Sprite operatorSprite;
	sf::Vector2f position;

	bool attackRangeVisible = false;
	std::vector<sf::RectangleShape> attackRangeRects;

	/*
	 * based on the position setting of the figureSprite
	 */
	sf::FloatRect collisionBox;

	std::vector<std::shared_ptr<Enemy>> inRangeEnemies;

	OperatorStatus status = OP_ST_IDLE;

public:
	Operator(nlohmann::json opData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer);

	int getId() const { return id; }

	void addInRangeEnemy(std::shared_ptr<Enemy> en) { inRangeEnemies.push_back(en); }
	void removeInRangeEnemy(int id);

	void setAttackRangeRects();
	std::vector<sf::RectangleShape> getAttackRangeRects() const { return attackRangeRects; }
	bool isInRange(const sf::Vector2f) const;

	void getHit(int damage) { currentHealth = safeSubtract(currentHealth, std::max(int(std::ceil(0.15 * damage)), damage - defenseAmount)); }
	void attemptAttack();

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event);

	~Operator() = default;
};
