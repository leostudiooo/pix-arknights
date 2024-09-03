// TextButton.h
#pragma once

#include "Button.h"

// 7px SMALL, 9px LARGE
enum FontSize { SMALL, LARGE };

class TextButton: public Button
{
protected:
	sf::Text text;
public:
	TextButton() = default;
	TextButton(std::string textString, std::shared_ptr<sf::Texture> normal_texture, std::shared_ptr<sf::Texture> hover_texture, std::shared_ptr<sf::Texture> click_texture, sf::Vector2f position, std::shared_ptr<Game> game, std::function<void()> onClick);

	void loadAssets();

	void setFontSize(FontSize size);
	
	void setTextOffset(sf::Vector2f offset) { text.setPosition(offset); }

	void setTextString(std::string textString) { text.setString(textString); }

	void setTextColor(sf::Color color) { text.setFillColor(color); }

	void setPosition(sf::Vector2f position);

	void render(sf::RenderWindow &window);
};