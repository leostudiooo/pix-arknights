// SplashScreen.h
#pragma once

#include "Button.h"
#include "Game.h"
#include "UserInterface.h"

#include <iostream>

class SplashScreen: public UserInterface
{
private:
	sf::Sprite backgroundSprite;
	std::shared_ptr<sf::Music> backgroundMusic;

	Button startButton;

public:
	SplashScreen(); // Default constructor
	SplashScreen(
		std::shared_ptr<sf::Texture> bg_texture,
		std::shared_ptr<sf::Music> bg_music,
		std::shared_ptr<sf::Texture> btn_normal_texture,
		std::shared_ptr<sf::Texture> btn_hover_texture,
		std::shared_ptr<sf::Texture> btn_click_texture,
		Game *game);
	void handleEvent(const sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
	~SplashScreen();
};