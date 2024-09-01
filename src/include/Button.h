// Button.h
#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Game;

class Button
{
private:
	sf::Sprite buttonSprite;
	std::vector<std::shared_ptr<sf::Texture> > textures;
	bool isPressed = false;
	bool isTriggered = false;
	std::function<void()> onClick;
	std::shared_ptr<Game> game;

public:
	Button(std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> pressed_texture, sf::Vector2f position, std::shared_ptr<Game> game, std::function<void()> onClick);

	void draw(sf::RenderWindow &window);
	void update();

	bool isMouseOver(sf::Vector2f mousePosition);

	void handleEvent(const sf::Event &event);

	~Button() = default;
};