#include "UserInterface.h"

SplashScreen::SplashScreen(
	std::shared_ptr<sf::Texture> bg_texture,
	std::shared_ptr<sf::Music> bg_music,
	std::shared_ptr<sf::Texture> btn_normal_texture,
	std::shared_ptr<sf::Texture> btn_hover_texture,
	std::shared_ptr<sf::Texture> btn_click_texture,
	Game *game)
	: startButton(
		  btn_normal_texture,
		  btn_hover_texture,
		  btn_click_texture,
		  sf::Vector2f(100, 100),
		  [game]()
		  {
			  game->pushState(std::make_unique<MainMenu>());
			  std::clog << "Button clicked! Switching to MainMenu." << std::endl;
		  })
{
	backgroundSprite.setTexture(*bg_texture);
	backgroundMusic = bg_music;
	backgroundMusic->setLoop(true);
	backgroundMusic->play();
}

void SplashScreen::handleEvent(const sf::Event &event)
{
	startButton.handleEvent(event);
}

void SplashScreen::render(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	startButton.draw(window);
}