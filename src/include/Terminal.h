// Terminal.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

#include "json.hpp"

#include <SFML/graphics.hpp>

using json = nlohmann::json;

class Terminal: public UserInterface
{
private:
	sf::Sprite backgroundSprite;

	Button backButton;
	Button homeButton;
	
	json levelData;
	std::vector<std::pair<sf::Text, std::shared_ptr<Button> > > levelList;

public:
	Terminal(std::shared_ptr<Game> game);
	void loadAssets() override;
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	~Terminal() override = default;

	void loadLevelList();
};