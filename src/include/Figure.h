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

	const sf::Vector2f _globalDrawOffset = {0, -3};
    const sf::Vector2f _tileOrigin = { 24, 16 };
    const int _tileSize = 16;
	const int _figHeight = 16;
public:
	Figure(std::shared_ptr<Combat> combat, std::shared_ptr<Game> game, std::shared_ptr<FigureLayer> figureLayer) : combat(combat), game(game), figureLayer(figureLayer) {}
	~Figure() = default;

	virtual void handleEvent(const sf::Event &) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &) = 0;
	std::shared_ptr<Figure> getThis() { return shared_from_this(); }
};
