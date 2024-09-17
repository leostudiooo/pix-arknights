// Settlement.h
#pragma once

#include "UserInterface.h"
#include "Button.h"

class Settlement : public UserInterface
{
private:
	std::string levelName;
	int rating;
	sf::Sprite background;
	sf::Text levelNameText;
	sf::Text title;
	std::vector<sf::Sprite> hexagonStars;
	Button continueButton;
public:
	Settlement(std::shared_ptr<Game> game, std::string levelName, int rating);
	~Settlement() = default;

	void loadAssets();
	
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	void playMusic() override;
};
