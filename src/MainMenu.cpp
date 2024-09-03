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

	game->bgMusic = game->getMusic("main_menu_bg_music");
	std::clog << "Playing main menu music" << std::endl;
	game->bgMusic->setLoop(true);
	game->bgMusic->play();

	terminalButton.setTextures(
		game->getTexture("terminal_normal"), 
		game->getTexture("terminal_hover"), 
		game->getTexture("terminal_click"));
	terminalButton.setPosition(sf::Vector2f(107, 6));
	terminalButton.setGame(game);
	terminalButton.setOnClick([game]()
	{
		// game->pushState(std::make_unique<Terminal>(game));
	});

	squadButton.setTextures(
		game->getTexture("squad_normal"), 
		game->getTexture("squad_hover"), 
		game->getTexture("squad_click"));
	squadButton.setPosition(sf::Vector2f(102, 34));
	squadButton.setGame(game);
	squadButton.setOnClick([game]()
	{
		// game->pushState(std::make_unique<Squad>(game));
	});

	operatorButton.setTextures(
		game->getTexture("operator_normal"), 
		game->getTexture("operator_hover"), 
		game->getTexture("operator_click"));
	operatorButton.setPosition(sf::Vector2f(145, 34));
	operatorButton.setGame(game);
	operatorButton.setOnClick([game]()
	{
		// game->pushState(std::make_unique<OperatorMenu>(game));
	});

	assistantSprite.setTexture(* game->getTexture("assistant_img"));
	assistantSprite.setPosition(20, 20);
}

void MainMenu::loadAssets()
{
	// Background image and music
	game->load(TEXTURE, "main_menu_bg_img", "main_menu/garden.png");
	game->load(MUSIC, "main_menu_bg_music", "main_menu/spring.mp3");

	// Button textures
	game->load(TEXTURE, "terminal_normal", "main_menu/terminal_normal.png");
	game->load(TEXTURE, "terminal_hover", "main_menu/terminal_hover.png");
	game->load(TEXTURE, "terminal_click", "main_menu/terminal_click.png");

	game->load(TEXTURE, "squad_normal", "main_menu/squad_normal.png");
	game->load(TEXTURE, "squad_hover", "main_menu/squad_hover.png");
	game->load(TEXTURE, "squad_click", "main_menu/squad_click.png");

	game->load(TEXTURE, "operator_normal", "main_menu/operator_normal.png");
	game->load(TEXTURE, "operator_hover", "main_menu/operator_hover.png");
	game->load(TEXTURE, "operator_click", "main_menu/operator_click.png");

	// Assistant image
	game->load(TEXTURE, "assistant_img", "Thorns_96x96.png");

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
	window.draw(assistantSprite);
}