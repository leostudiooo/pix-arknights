#include "TextButton.h"

#include "Game.h"

TextButton::TextButton(
	std::string textString,
	std::shared_ptr<sf::Texture> normal_texture,
	std::shared_ptr<sf::Texture> hover_texture,
	std::shared_ptr<sf::Texture> click_texture,
	sf::Vector2f position,
	std::shared_ptr<Game> game,
	std::function<void()> onClick) : Button(normal_texture,
											hover_texture,
											click_texture,
											position,
											game,
											onClick)
{
	loadAssets();
	text.setString(textString);
	text.setOrigin(position);
}

void TextButton::setFontSize(FontSize size)
{
	switch (size)
	{
	case SMALL:
		text.setFont(*game->getFont("font_small"));
		text.setCharacterSize(7);
		break;

	case LARGE:
		text.setFont(*game->getFont("font_large"));
		text.setCharacterSize(9);
		break;
	default:
		break;
	}
}

void TextButton::loadAssets()
{
	game->load(FONT, "font_small", "dinkie-7px-demo.ttf");
	game->load(FONT, "font_large", "dinkie-9px-demo.ttf");
}

void TextButton::setPosition(sf::Vector2f position)
{
	Button::setPosition(position);
	text.setOrigin(position);
}

void TextButton::render(sf::RenderWindow &window)
{
	window.draw(text);
	Button::render(window);
}