#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Game.h"
#include "Button.h"

#include <iostream>

SplashScreen::SplashScreen(std::shared_ptr<Game> game)
{
	backgroundSprite.setTexture(* game->assetManager.getTexture("splash_bg_img"));
	backgroundSprite.setPosition(0,0);
	backgroundMusic = game->assetManager.getMusic("splash_bg_music");
	
	startButton.setTextures(game->assetManager.getTexture("start_normal"), game->assetManager.getTexture("start_hover"), game->assetManager.getTexture("start_click"));
	startButton.setPosition(sf::Vector2f(69,60));
	startButton.setOnClick([&]()
	{
		game->assetManager.getMusic("splash_bg_music")->stop();
		game->popState();
		// game->pushState(std::make_unique<MainMenu>(game));
	});

	backgroundMusic->setLoop(true);
	backgroundMusic->play();
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