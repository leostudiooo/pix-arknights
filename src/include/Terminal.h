// Terminal.h
#pragma once

#include "Button.h"
#include "UserInterface.h"

class Terminal: public UserInterface
{
private:
	sf::Sprite backgroundSprite;
	std::shared_ptr<sf::Music> backgroundMusic;

	Button backButton;
	
};