#include "MainMenu.h"

#include "Terminal.h"
#include "Squad.h"
#include "OperatorMenu.h"

#include "Game.h"
#include "AssetType.h"

#include <fstream>

#include <memory>

MainMenu::MainMenu(std::shared_ptr<Game> game) : UserInterface(game)
{
	loadAssets();

	backgroundSprite.setTexture(*game->getTexture("main_menu_bg_img"));
	backgroundSprite.setPosition(0, 0);

	terminalButton.setTextures(
		game->getTexture("terminal_normal"),
		game->getTexture("terminal_hover"),
		game->getTexture("terminal_click"));
	terminalButton.setPosition(sf::Vector2f(107, 6));
	terminalButton.setGame(game);
	terminalButton.setOnClick([game]()
							  {
			auto newGame = game->getGame();
			newGame->pushState(std::make_shared<Terminal>(newGame)); });

	squadButton.setTextures(
		game->getTexture("squad_normal"),
		game->getTexture("squad_hover"),
		game->getTexture("squad_click"));
	squadButton.setPosition(sf::Vector2f(102, 34));
	squadButton.setGame(game);
	squadButton.setOnClick([game]()
						   {
							   // game->pushState(std::make_shared<Squad>(game));
						   });

	operatorButton.setTextures(
		game->getTexture("operator_normal"),
		game->getTexture("operator_hover"),
		game->getTexture("operator_click"));
	operatorButton.setPosition(sf::Vector2f(145, 34));
	operatorButton.setGame(game);
	operatorButton.setOnClick([game]()
							  {
								  // game->pushState(std::make_shared<OperatorMenu>(game));
							  });

	assistantSprite.setTexture(*game->getTexture("assistant_img"));
	assistantSprite.setPosition(assistantPos.first, assistantPos.second);

	titleText.setFont(*game->getFont("font_small"));
	titleText.setString(L"Pixnights 开发中");
	titleText.setCharacterSize(8); // though designed 7, set for 8 for no resampling (don't know why)
	titleText.setFillColor(sf::Color(0xffffffff));
	titleText.setPosition(round(120), round(92));
}

void MainMenu::loadAssets()
{
	using json = nlohmann::json;
	std::fstream settingsFile(game->getAssetPrefix() + "main_menu/settings.json");
	if (!settingsFile.is_open())
	{
		std::cerr << "Failed to open main menu settings file" << std::endl;
		// Background image and music
		game->load(TEXTURE, "main_menu_bg_img", "main_menu/bg.png");
		game->load(MUSIC, "main_bg_music", "main_menu/bg.mp3");
		// Assistant image
		game->load(TEXTURE, "assistant_img", "main_menu/Thorns_96x96.png");
		assistantPos = std::make_pair(20, 20);
	}
	else
	{
		std::clog << "Opened main menu settings file" << std::endl;
		settings = json::parse(settingsFile);
		settingsFile.close();
		// Debug
		std::clog << settings << std::endl;
		// {"assets":{"assistant_img":{"name":"assistant_img","path":"main_menu/assistant.png","type":0},"main_menu_bg_img":{"name":"main_menu_bg_img","path":"main_menu/bg.png","type":0},"main_music":{"name":"main_bg_music","path":"main_menu/bg.mp3","type":1}},"assistantPos":[20,20]}
		for (auto &asset : settings["assets"])
		{
			std::string name = asset["name"];
			std::string path = asset["path"];
			int type = asset["type"];
			switch (type)
			{
			case 0:
				game->load(TEXTURE, name, path);
				break;
			case 1:
				game->load(MUSIC, name, path);
				break;
			case 2:
				game->load(FONT, name, path);
				break;
			default:
				std::cerr << "Unknown asset type" << std::endl;
				break;
			}
		}
		int posX = settings["assistantPos"][0];
		int posY = settings["assistantPos"][1];
		assistantPos = std::make_pair(posX, posY);
	}

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
	terminalButton.render(window);
	// squadButton.render(window);
	// operatorButton.render(window);
	window.draw(assistantSprite);
	window.draw(titleText);
}

void MainMenu::playMusic()
{
	if (game->bgMusic)
		game->bgMusic->stop();
	game->bgMusic = game->getMusic("main_bg_music");
	game->bgMusic->setLoop(true);
	game->bgMusic->play();
	std::clog << "Playing main menu music" << std::endl;
}
