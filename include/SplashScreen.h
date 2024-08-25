// SplashScreen.h
#pragma once

#include "Button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SplashScreen
{
private:
	sf::Sprite backgroundSprite;
	std::shared_ptr<sf::Music> backgroundMusic;

	Button startButton;

public:
	SplashScreen(std::shared_ptr<sf::Texture> bg_texture, std::shared_ptr<sf::Music> bg_music);
	~SplashScreen();
};