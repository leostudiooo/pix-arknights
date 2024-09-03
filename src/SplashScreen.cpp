#include "SplashScreen.h"

#include "MainMenu.h"

#include "Game.h"

#include <iostream>

SplashScreen::SplashScreen(std::shared_ptr<Game> game): UserInterface(game)
{
	loadAssets();

	backgroundSprite.setTexture(* game->getTexture("splash_bg_img"));
	backgroundSprite.setPosition(0,0);
	
	game->bgMusic = game->getMusic("splash_bg_music");
	
	startButton.setTextures(game->getTexture("start_normal"), game->getTexture("start_hover"), game->getTexture("start_click"));
	
	startButton.setPosition(sf::Vector2f(69,60));
	startButton.setGame(game->getGame());
	startButton.setOnClick([game]()
	{
		auto newGame = game->getGame();
		newGame->popState(true);
		newGame->pushState(std::make_unique<MainMenu>(newGame), true);
	});

	game->bgMusic->setLoop(true);
	game->bgMusic->play();
}

void SplashScreen::loadAssets()
{
	// Background image and music
	game->load(TEXTURE, "splash_bg_img", "splash/bg.png");
	game->load(MUSIC, "splash_bg_music", "splash/bg.mp3");

	// Button textures
	game->load(TEXTURE, "start_normal", "splash/start_normal.png");
	game->load(TEXTURE, "start_hover", "splash/start_hover.png");
	game->load(TEXTURE, "start_click", "splash/start_click.png");
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
	startButton.render(window);
}