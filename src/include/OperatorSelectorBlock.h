// OperatorSelectorBlock.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class OperatorSelectorBlock
{
protected:
	sf::RectangleShape edgeShape;
	sf::Sprite previewImg;
	sf::Text opInfo;
	sf::RectangleShape undeployableMask;
	sf::Vector2f position;
	bool isSelected = false;
	bool undeployable = false;

public:
	OperatorSelectorBlock() = default;
	OperatorSelectorBlock(std::shared_ptr<sf::Texture> preview, const sf::Vector2f position, const std::string opInfoStr, std::shared_ptr<sf::Font> font);

	void setSelected(bool selected);
	bool getSelected() const;

	void setUndeployable(bool undeployable) { this->undeployable = undeployable; }

	void update();
	void render(sf::RenderWindow &window);
	void handleEvent(const sf::Event &event);
};