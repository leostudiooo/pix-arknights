// Button.h
#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Sprite buttonSprite;
	std::vector<std::shared_ptr<sf::Texture>> textures;
	bool isPressed = false;

public:
	Button(std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> pressed_texture, sf::Vector2f position);
	// hover and press events
	void hover();
	void press();
	void release();

	~Button();
};