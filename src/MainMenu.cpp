#include "MainMenu.h"

#include "Terminal.h"
#include "Squad.h"
#include "OperatorMenu.h"

#include "Game.h"
#include "AssetType.h"

#include <memory>

MainMenu::MainMenu(std::shared_ptr<Game> game): UserInterface(game)
{
	loadAssets();

	backgroundSprite.setTexture(* game->getTexture("main_menu_bg_img"));
	backgroundSprite.setPosition(0,0);

	backgroundMusic = game->getMusic("main_menu_bg_music");
	backgroundMusic->setLoop(true);
	backgroundMusic->play();

	terminalButton.setTextures(
		game->getTexture("terminal_normal"), 
		game->getTexture("terminal_hover"), 
		game->getTexture("terminal_click"));
	terminalButton.setPosition(sf::Vector2f(107, 6));
	terminalButton.setGame(game);
	terminalButton.setOnClick([&]()
	{
		// game->pushState(std::make_unique<Terminal>(game));
	});

	squadButton.setTextures(
		game->getTexture("squad_normal"), 
		game->getTexture("squad_hover"), 
		game->getTexture("squad_click"));
	squadButton.setPosition(sf::Vector2f(102, 34));
	squadButton.setGame(game);
	squadButton.setOnClick([&]()
	{
		// game->pushState(std::make_unique<Squad>(game));
	});

	operatorButton.setTextures(
		game->getTexture("operator_normal"), 
		game->getTexture("operator_hover"), 
		game->getTexture("operator_click"));
	operatorButton.setPosition(sf::Vector2f(145, 34));
	operatorButton.setGame(game);
	operatorButton.setOnClick([&]()
	{
		// game->pushState(std::make_unique<OperatorMenu>(game));
	});
}

void MainMenu::loadAssets()
{
	// Background image and music
	game->load(TEXTURE, "main_menu_bg_img", "img/main_menu/bg.png");
	game->load(MUSIC, "main_menu_bg_music", "audio/");

	// Button textures
	game->load(TEXTURE, "terminal_normal", "img/main_menu/terminal_normal.png");
	game->load(TEXTURE, "terminal_hover", "img/main_menu/terminal_hover.png");
	game->load(TEXTURE, "terminal_click", "img/main_menu/terminal_click.png");

	game->load(TEXTURE, "squad_normal", "img/main_menu/squad_normal.png");
	game->load(TEXTURE, "squad_hover", "img/main_menu/squad_hover.png");
	game->load(TEXTURE, "squad_click", "img/main_menu/squad_click.png");

	game->load(TEXTURE, "operator_normal", "img/main_menu/operator_normal.png");
	game->load(TEXTURE, "operator_hover", "img/main_menu/operator_hover.png");
	game->load(TEXTURE, "operator_click", "img/main_menu/operator_click.png");

}

void MainMenu::handleEvent(const sf::Event &event)
{
	terminalButton.handleEvent(event);
	squadButton.handleEvent(event);
	operatorButton.handleEvent(event);
}

void MainMenu::update()
{
	terminalButton.update();
	squadButton.update();
	operatorButton.update();
}

void MainMenu::render(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	terminalButton.draw(window);
	squadButton.draw(window);
	operatorButton.draw(window);
}