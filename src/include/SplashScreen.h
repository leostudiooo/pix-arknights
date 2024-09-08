// SplashScreen.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

#include <memory>
#include <sfml/Graphics.hpp>
#include <sfml/Audio.hpp>

class Game;

class SplashScreen: public UserInterface
{
private:
	sf::Sprite backgroundSprite;

	Button startButton;

public:
	SplashScreen(); // Default constructor
	SplashScreen(std::shared_ptr<Game> game);
	void loadAssets();
	void handleEvent(const sf::Event &event) override;
	void update() override;
	void render(sf::RenderWindow &window) override;
	~SplashScreen() override = default;
};