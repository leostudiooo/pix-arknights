// Enemy.h
#pragma once

#include "Figure.h"

enum EnemyType
{
	SLUG,
	SOLIDER,
	LIGHTSHIELD
};

class Enemy: protected Figure
{
private:
	const EnemyType type;
	const int moveSpeed; // in pixels per frame
	const int collisionBox[4] = {16, 16, 0, 32}; // {right, left, bottom, top}, based on the bottom-center of the enemy sprite (32*32 px)

	int position[2];
	int direction[2];

	// Enemy image[3]: 32*32 px, status {regular, move, attack}

public:
	Enemy(int maxHealth, int attackDamage, int attackInterval, int defenseAmount, EnemyType type, int moveSpeed, int position[2], int direction[2]) : Figure(maxHealth, attackDamage, attackInterval, defenseAmount), type(type), moveSpeed(moveSpeed)
	{
		this->position[0] = position[0];
		this->position[1] = position[1];
		this->direction[0] = direction[0];
		this->direction[1] = direction[1];
	}
	~Enemy();
};