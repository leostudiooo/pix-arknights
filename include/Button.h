// Button.h
#pragma once

#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::Sprite buttonSprite;
	std::vector<std::shared_ptr<sf::Texture>> textures;
	bool isPressed = false;

	std::function<void()> onClick;

public:
	Button(std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> pressed_texture, sf::Vector2f position, std::function<void()> onClick);

	void draw(sf::RenderWindow &window);

	bool isMouseOver(sf::Vector2f mousePosition);

	void handleEvent(const sf::Event &event);

	~Button();
};