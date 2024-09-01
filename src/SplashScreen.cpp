#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Game.h"
#include "Button.h"

#include <iostream>

SplashScreen::SplashScreen(
	std::shared_ptr<sf::Texture> bg_texture,
	std::shared_ptr<sf::Music> bg_music,
	std::shared_ptr<sf::Texture> btn_normal_texture,
	std::shared_ptr<sf::Texture> btn_hover_texture,
	std::shared_ptr<sf::Texture> btn_click_texture,
	std::shared_ptr<Game> game)
	: startButton(
		  btn_normal_texture,
		  btn_hover_texture,
		  btn_click_texture,
		  sf::Vector2f(69, 60),
		  game,
		  [game]()
		  {
			  //   game->pushState(std::make_unique<MainMenu>());
			  std::clog << "Button clicked! Switching to MainMenu." << std::endl;
		  })
{
	std::clog << "SplashScreen constructor" << std::endl;
	backgroundSprite.setTexture(*bg_texture);
	backgroundSprite.setPosition(0, 0);
	std::clog << "Background sprite texture set" << std::endl;
	std::clog << "Texture size: " << bg_texture->getSize().x << ", " << bg_texture->getSize().y << std::endl;
	backgroundMusic = bg_music;
	backgroundMusic->setLoop(true);
	backgroundMusic->play();
	std::clog << "Music playing" << std::endl;
}

void SplashScreen::handleEvent(const sf::Event &event)
{
	startButton.handleEvent(event);
}

void SplashScreen::update()
{
	startButton.update();
}

void SplashScreen::render(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	startButton.draw(window);
}