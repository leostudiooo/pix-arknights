// Figure.h
#pragma once

#include "Game.h"

/*
 * `Figure` class is the base class for all characters in the game.
 * It contains the basic attributes and methods that all characters should have, including:
 * - `maxHealth`: the maximum health points of the character
 * - `currentHealth`: the current health points of the character
 * - `attackDamage`: the amount of damage the character can cause
 * - `attackInterval`: the time interval between each attack (in frames)
 * - `defenseAmount`: the amount of damage the character can block
 * - `figureSprite`: the sprite of the character
 */
class Figure
{
private:
	const std::string name;
	const int maxHealth;
	int currentHealth;
	const int attackDamage;
	const int attackInterval;
	const int defenseAmount;

	sf::Sprite figureSprite;
public:
	Figure(int maxHealth, int attackDamage, int attackInterval, int defenseAmount) : maxHealth(maxHealth), attackDamage(attackDamage), attackInterval(attackInterval), defenseAmount(defenseAmount)
	{
		currentHealth = maxHealth;
	}
	~Figure();
};