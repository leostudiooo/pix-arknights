// OperatorSelectorBlock.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class OperatorSelectorBlock
{
protected:
	std::string opName;

	sf::RectangleShape edgeShape;
	sf::Sprite previewImg;
	sf::Text opInfo;
	sf::RectangleShape undeployableMask;
	sf::Vector2f position;
	sf::Vector2f mousePosition;
	bool isPressed = false;
	bool isSelected = false;
	bool undeployable = true;

public:
	OperatorSelectorBlock() = default;
	OperatorSelectorBlock(const std::string &opName, std::shared_ptr<sf::Texture> preview, const sf::Vector2f position, const std::string opInfoStr, std::shared_ptr<sf::Font> font);

	void setSelected(bool selected) { isSelected = selected; }
	bool getSelected() const { return isSelected; }

	std::string getOpName() const { return opName; }

	void setUndeployable(bool undeployable) { this->undeployable = undeployable; }

	void update();
	void render(sf::RenderWindow &window);
	void handleEvent(const sf::Event &event);

	void setMousePosition(sf::Vector2f mousePosition) { this->mousePosition = mousePosition; }

	bool isMouseOver()
	{
		return edgeShape.getGlobalBounds().contains(mousePosition);
	}
};