// UserInterface.h
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

class Game;

class UserInterface
{
protected:
	std::shared_ptr<Game> game;
public:
	UserInterface() = default;
	UserInterface(std::shared_ptr<Game> game) : game(game) {}
	virtual ~UserInterface() = default;
	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
};