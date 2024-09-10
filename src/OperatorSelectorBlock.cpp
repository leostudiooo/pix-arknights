#include "OperatorSelectorBlock.h"

#include <iostream>

OperatorSelectorBlock::OperatorSelectorBlock(const std::string &opName, const unsigned int opCost, std::shared_ptr<sf::Texture> preview, const sf::Vector2f position, const std::string opInfoStr, std::shared_ptr<sf::Font> font) : position(position), opName(opName), opCost(opCost)
{
	edgeShape.setPosition(position);
	edgeShape.setSize(sf::Vector2f(16, 16));
	edgeShape.setFillColor(sf::Color(0x22222299));
	edgeShape.setOutlineColor(sf::Color(0xbbbbbbff));
	edgeShape.setOutlineThickness(1);

	previewImg.setTexture(*preview);
	previewImg.setPosition(position);

	opInfo.setFont(*font);
	opInfo.setCharacterSize(8);
	opInfo.setFillColor(sf::Color::White);
	opInfo.setPosition(position + sf::Vector2f(1, -5));
	opInfo.setString(opInfoStr);

	undeployableMask.setPosition(position);
	undeployableMask.setSize(sf::Vector2f(16, 16));
	undeployableMask.setFillColor(sf::Color(0x00000088));
}

void OperatorSelectorBlock::update()
{
	if (isSelected && !undeployable)
	{
		position.y = 92 - 6;
		edgeShape.setPosition(position);
		previewImg.setPosition(position);
		opInfo.setPosition(position + sf::Vector2f(1, 14));
	}
	else
	{
		position.y = 92;
		edgeShape.setPosition(position);
		previewImg.setPosition(position);
		opInfo.setPosition(position + sf::Vector2f(1, -5));
	}
}

void OperatorSelectorBlock::render(sf::RenderWindow &window)
{
	window.draw(edgeShape);
	window.draw(previewImg);
	if (undeployable)
		window.draw(undeployableMask);
	window.draw(opInfo);
}

void OperatorSelectorBlock::handleEvent(const sf::Event &event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (isMouseOver())
		{
			if(!isPressed) isSelected = !isSelected;
			isPressed = !isPressed;
		}
	}
}