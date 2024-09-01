// UserInterface.h
#pragma once

#include "Button.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class UserInterface
{
public:
	virtual void handleEvent(const sf::Event &event) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow &window) = 0;
};

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
		std::shared_ptr<Game> game);
	void handleEvent(const sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
	~SplashScreen();
};

class MainMenu: public UserInterface
{
public:
	void handleEvent(const sf::Event &event);
	void update();
	void render(sf::RenderWindow &window);
};