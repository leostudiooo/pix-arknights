#pragma once

#include "Figure.h"

/*
 * `OperatorType` is an enumeration type that represents the type of the Operator.
 * It can be either `MELEE` or `RANGED`.
 */
enum OperatorType
{
	MELEE,
	RANGED
};

/*
 * `OperatorBranch` is an enumeration type that represents the branch of the Operator.
 * It can be `DEFENDER`, `GUARD`, `MEDIC`, or `SNIPER`.
 */
enum OperatorBranch
{
	DEFENDER,
	GUARD,
	MEDIC,
	SNIPER
};

class Operator : protected Figure
{
private:
	const OperatorType type;
	const OperatorBranch branch;
	const int blockNumber;

	/*
	 * `attackRange` is an 2D-array that represents the attack range of the Operator, based on the Operator's own frame.
	 */
	int attackRange[2];

	/*
	 * `direction` is an 2D-array that represents the direction of the Operator, based on the game frame.
	 * Game frame:
	 * → x, ↓ y
	 * - [1, 0] -> right
	 * - [-1, 0] -> left
	 * - [0, 1] -> down
	 * - [0, -1] -> up
	 */
	int direction[2];
	int position[2];

	// Operator image[2]: 32*32 px, status {regular, attack}
	// TODO: image data type?

	int deployCost;
	int redeployInterval; // in frames

public:
	Operator(int maxHealth, int attackDamage, int attackInterval, int defenseAmount, OperatorType type, OperatorBranch branch, int blockNumber, int attackRange[2], int direction[2], int position[2], int deployCost, int redeployInterval) : Figure(maxHealth, attackDamage, attackInterval, defenseAmount), type(type), branch(branch), blockNumber(blockNumber), deployCost(deployCost), redeployInterval(redeployInterval)
	{
		this->attackRange[0] = attackRange[0];
		this->attackRange[1] = attackRange[1];
		this->direction[0] = direction[0];
		this->direction[1] = direction[1];
		this->position[0] = position[0];
		this->position[1] = position[1];
	}
	void deploy();
	void retreat();
	~Operator();
};