// Figure.h
#pragma once

#include "Game.h"

class Combat;
class FigureLayer;
class CombatEvent;

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
class Figure : public std::enable_shared_from_this<Figure>
{
protected:
	std::string name = "";
	int id;
	int maxHealth = 0;
	int currentHealth = 0;
	int attackDamage = 0;
	int attackInterval = 0;
	int defenseAmount = 0;

	sf::Sprite figureSprite;

	std::shared_ptr<Combat> combat;
	std::shared_ptr<Game> game;
	std::shared_ptr<FigureLayer> figureLayer;

	sf::RectangleShape healthBar;

	const sf::Vector2f _globalDrawOffset = {0, -3};
	const sf::Vector2f _tileOrigin = {24, 16};
	const int _tileSize = 16;
	const int _figHeight = 16;

public:
	Figure(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : combat(combat), game(game), figureLayer(figureLayer) {}
	~Figure() = default;

	virtual void handleEvent(const sf::Event &) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &) = 0;
	std::shared_ptr<Figure> getThis() { return shared_from_this(); }

	sf::Vector2f tileToWorld(const sf::Vector2i &tilePos) const
	{
		return sf::Vector2f(tilePos.x * _tileSize + _tileOrigin.x + _globalDrawOffset.x, tilePos.y * _tileSize + _tileOrigin.y + _globalDrawOffset.y);
	}
	sf::Vector2f tileToWorld(const std::vector<int> &tilePos) const
	{
		return sf::Vector2f(tilePos[0] * _tileSize + _tileOrigin.x + _globalDrawOffset.x, tilePos[1] * _tileSize + _tileOrigin.y + _globalDrawOffset.y);
	}

	unsigned int safeSubtract(unsigned int a, unsigned int b) { return a > b ? a - b : 0; }
	unsigned int safeAdd(unsigned int a, unsigned int b, unsigned int m) { return a + b < m ? a + b : m; }
};
