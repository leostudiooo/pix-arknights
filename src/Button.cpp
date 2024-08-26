#include "Button.h"

Button::Button(std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> pressed_texture, sf::Vector2f position, std::function<void()> onClick)
{
	textures.push_back(normal_texture);
	textures.push_back(hover_texture);
	textures.push_back(pressed_texture);

	buttonSprite.setTexture(*textures[0]);
	buttonSprite.setPosition(position);

	this->onClick = onClick;
}

void Button::draw(sf::RenderWindow &window)
{
	window.draw(buttonSprite);
}

bool Button::isMouseOver(sf::Vector2f mousePosition)
{
	return buttonSprite.getGlobalBounds().contains(mousePosition);
}

void Button::handleEvent(const sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (isMouseOver(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			buttonSprite.setTexture(*textures[2]);
			isPressed = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (
			isPressed &&
			event.mouseButton.button == sf::Mouse::Left &&
			isMouseOver(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			buttonSprite.setTexture(*textures[1]);
			isPressed = false;
			onClick();
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (isMouseOver(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
		{
			buttonSprite.setTexture(*textures[1]);
		}
		else
		{
			buttonSprite.setTexture(*textures[0]);
		}
	}
}