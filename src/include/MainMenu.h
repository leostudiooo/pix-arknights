// MainMenu.h
# pragma once

#include "UserInterface.h"

class MainMenu: public UserInterface
{
public:
	void handleEvent(const sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
};