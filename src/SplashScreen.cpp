#include "SplashScreen.h"

SplashScreen::SplashScreen(
	std::shared_ptr<sf::Texture> bg_texture,
	std::shared_ptr<sf::Music> bg_music,
	std::shared_ptr<sf::Texture> btn_normal_texture,
	std::shared_ptr<sf::Texture> btn_hover_texture,
	std::shared_ptr<sf::Texture> btn_click_texture,
	GameState &gameState)
	: startButton(
		  btn_normal_texture,
		  btn_hover_texture,
		  btn_click_texture,
		  sf::Vector2f(100, 100),
		  [&gameState]()
		  {
			  gameState = GameState::MAIN_MENU;
			  std::clog << "Button clicked! Switching to MainMenu." << std::endl;
		  })
{
	backgroundSprite.setTexture(*bg_texture);
	backgroundMusic = bg_music;
}

void SplashScreen::draw(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	startButton.draw(window);
	backgroundMusic->setLoop(true);
	backgroundMusic->play();
}

void SplashScreen::stop()
{
	backgroundMusic->stop();
}