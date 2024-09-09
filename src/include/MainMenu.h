// MainMenu.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

#include "json.hpp"

class MainMenu: public UserInterface
{
private:
	sf::Sprite backgroundSprite;
	sf::Sprite assistantSprite;

	Button terminalButton;
	Button squadButton;
	Button operatorButton;

	sf::Text titleText;

	nlohmann::json settings;
	std::pair<int,int> assistantPos;

public:
	MainMenu(std::shared_ptr<Game> game);
	~MainMenu() override = default;

	void loadAssets();
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
    void playMusic() override;
};
