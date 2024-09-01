// UserInterface.h
#pragma once

#include <SFML/window.hpp>
#include <SFML/Graphics.hpp>

class Game;

class UserInterface
{
public:
	virtual ~UserInterface() = default;
	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
};