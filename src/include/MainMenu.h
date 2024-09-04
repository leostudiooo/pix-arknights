// MainMenu.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

class MainMenu: public UserInterface
{
private:
	sf::Sprite backgroundSprite;
	sf::Sprite assistantSprite;

	Button terminalButton;
	Button squadButton;
	Button operatorButton;

	sf::Text titleText;

public:
	MainMenu(std::shared_ptr<Game> game);
	void loadAssets() override;
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	~MainMenu() override = default;
};