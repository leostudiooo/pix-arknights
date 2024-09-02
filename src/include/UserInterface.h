// UserInterface.h
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game;

class UserInterface
{
protected:
	std::shared_ptr<Game> game;

	UserInterface() = default;
	UserInterface(std::shared_ptr<Game> game) : game(game) {}
public:
	virtual ~UserInterface() = default;
	virtual void loadAssets() = 0;
	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
};