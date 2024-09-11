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

enum OperatorStatus
{
	OP_ST_IDLE,
	OP_ST_ATTACK
};

class Operator : protected Figure
{
private:
	OperatorType type;
	OperatorBranch branch;
	unsigned int blockNumber;

	/*
	 * `attackRange` is a 2D-array that represents the attack range of the Operator, based on the Operator's own frame (facing right).
	 * e.g. a typical sniper has an attack range of
	 * [ [1, 1, 1, 0],
	 * ..[1, 1, 1, 1],
	 * ..[1, 1, 1, 0] ]
	 * and a typical guard has an attack range of
	 * [[1, 1]]
	 */
	std::vector<std::vector<bool> > attackRange;

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
	std::vector<std::shared_ptr<sf::Texture> > operatorTextures;
	sf::Sprite operatorSprite;
	sf::Vector2f position;

public:
	Operator(nlohmann::json opData, std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer);

	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void handleCombatEvent(const std::shared_ptr<CombatEvent> event);

	~Operator() = default;
};