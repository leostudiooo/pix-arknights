// SplashScreen.h
#pragma once

#include "UserInterface.h"
#include "Button.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class SplashScreen
{
private:
	sf::Sprite backgroundSprite;
	std::shared_ptr<sf::Music> backgroundMusic;

	Button startButton;

public:
	SplashScreen(
		std::shared_ptr<sf::Texture> bg_texture,
		std::shared_ptr<sf::Music> bg_music,
		std::shared_ptr<sf::Texture> btn_normal_texture,
		std::shared_ptr<sf::Texture> btn_hover_texture,
		std::shared_ptr<sf::Texture> btn_click_texture,
		GameState &gameState);
	void draw(sf::RenderWindow &window);
	void stop();
	~SplashScreen();
};