#include "Button.h"
#include "Game.h"

#include <iostream>

Button::Button(std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> click_texture, sf::Vector2f position, std::shared_ptr<Game> game, std::function<void()> onClick)
{
	textures.push_back(normal_texture);
	textures.push_back(hover_texture);
	textures.push_back(click_texture);

	buttonSprite.setTexture(*textures[0]);
	buttonSprite.setPosition(position);

	this->game = game;
	this->onClick = onClick;
}

void Button::render(sf::RenderWindow &window)
{
	window.draw(buttonSprite);
}

void Button::update()
{
	if (isPressed) isTriggered = true;
	else if (isTriggered)
	{
		isTriggered = false;
		buttonSprite.setTexture(*textures[1]);
		std::clog << "Button triggered" << std::endl;
		onClick();
	}
}

bool Button::isMouseOver(sf::Vector2f mousePosition)
{
	return buttonSprite.getGlobalBounds().contains(mousePosition);
}

void Button::handleEvent(const sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (isMouseOver(game->getMousePosition()))
		{
			buttonSprite.setTexture(*textures[2]);
			isPressed = !isPressed;
		}
		else
		{
			isPressed = false;
			isTriggered = false;
			buttonSprite.setTexture(*textures[0]);
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (isPressed) return;
		if (isMouseOver(game->getMousePosition()))
		{
			buttonSprite.setTexture(*textures[1]);
		}
		else
		{
			buttonSprite.setTexture(*textures[0]);
		}
	}
}