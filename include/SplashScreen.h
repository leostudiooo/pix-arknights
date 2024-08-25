// SplashScreen.h
#pragma once

#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SplashScreen
{
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::Music backgroundMusic;
	Button startButton;
public:
	SplashScreen(sf::Sprite backgroundSprite, sf::Texture backgroundTexture, sf::Music backgroundMusic, Button startButton);
	~SplashScreen();
};