// Button.h
#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Texture normalTexture;
	sf::Texture hoverTexture;
	sf::Texture pressedTexture;
	sf::Sprite buttonSprite;

public:
	Button(sf::Texture normalTexture, sf::Texture hoverTexture, sf::Texture pressedTexture, sf::Vector2f position);
	~Button();
};