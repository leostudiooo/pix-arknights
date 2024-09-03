#include "Terminal.h"

#include "Combat.h"
#include "MainMenu.h"

#include "Game.h"

#include <fstream>

Terminal::Terminal(std::shared_ptr<Game> game) : UserInterface(game)
{
	loadAssets();
	loadLevelList();

	backgroundSprite.setPosition(0,0);
	backgroundSprite.setTexture(* game->getTexture("terminal_bg"));

	for (auto &level : levelData["levels"])
	{
		float xPosition = 32.0f;

		std::string levelName;

		try
		{
			levelName = level["name"];
			std::clog << "Loaded level " << levelName << std::endl;
		}
		catch (const std::exception&)
		{
			std::cerr << "Error loading level " << level["name"] << std::endl;
		}

		auto textButton = std::make_shared<TextButton>(
			levelName,
			game->getTexture("lvl_normal"),
			game->getTexture("lvl_hover"),
			game->getTexture("lvl_click"),
			sf::Vector2f(xPosition, 32),
			game,
			[levelName, game]()
			{
				// auto newGame = game->getGame();
				// newGame->pushState(std::make_unique<Combat>(newGame, levelName["map"]));
			}
		);

		textButton->setTextString(levelName);

		textButton->setFontSize(SMALL);
		// textButton->setTextOffset(sf::Vector2f(1, 1));
		textButton->setTextColor(sf::Color(0xddddddff));

		levelList.push_back(textButton);

		xPosition += 32;
	}

	backButton.setTextures(
		game->getTexture("back_normal"),
		game->getTexture("back_hover"),
		game->getTexture("back_click"));
	backButton.setGame(game);
	backButton.setPosition(sf::Vector2f(6, 5));
	backButton.setOnClick(
		[game]()
		{
			auto newGame = game->getGame(); 
			newGame->popState(); 
		});

	homeButton.setTextures(
		game->getTexture("home_normal"),
		game->getTexture("home_hover"),
		game->getTexture("home_click")
	);
	homeButton.setGame(game);
	homeButton.setPosition(sf::Vector2f(30,5));
	homeButton.setOnClick(
		[game]()
		{
			auto newGame = game->getGame();
			while(newGame->popStateNoTransition());
			newGame->pushState(std::make_unique<MainMenu>(newGame));
		}
	);

	game->bgMusic = game->getMusic("main_bg_music");
}

void Terminal::loadAssets()
{
	game->load(TEXTURE, "terminal_bg", "terminal/bg.png");
	game->load(TEXTURE, "lvl_normal", "terminal/normal.png");
	game->load(TEXTURE, "lvl_hover", "terminal/hover.png");
	game->load(TEXTURE, "lvl_click", "terminal/click.png");
}

void Terminal::handleEvent(const sf::Event &event)
{
	for (auto& button : levelList)
	{
		button->handleEvent(event);
	}

	backButton.handleEvent(event);
	homeButton.handleEvent(event);
}

void Terminal::update()
{
	for (auto& button : levelList)
	{
		button->update();
	}
	backButton.update();
	homeButton.update();
}

void Terminal::render(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	for (auto& button : levelList)
	{
		button->render(window);
	}

	backButton.render(window);
	homeButton.render(window);
}



void Terminal::loadLevelList()
{
	std::ifstream file(game->getAssetPrefix() + "levels/levels.json");
	/* example levels.json
	{
		"levels": [
			{
				"name": "0-1",
				"map": "0-1.json"
			},
			{
				"name": "0-2",
				"map": "0-2.json"
			}
		]
	}
	*/
	try
	{
		levelData = json::parse(file);
	}
	catch (const std::exception&)
	{
		std::cerr << "Error parsing levels.json" << std::endl;
	}
}