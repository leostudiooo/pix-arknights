// MainMenu.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

class MainMenu: public UserInterface
{
private:
	sf::Sprite backgroundSprite;
	std::shared_ptr<sf::Music> backgroundMusic;

	Button terminalButton;
	Button squadButton;
	Button operatorButton;

public:
	MainMenu(std::shared_ptr<Game> game);
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	~MainMenu() override = default;
};