#include "Terminal.h"

#include "Combat.h"
#include "MainMenu.h"
#include "CombatMap.h"
#include "Game.h"

#include <fstream>

Terminal::Terminal(std::shared_ptr<Game> game) : UserInterface(game)
{
	loadAssets();
	loadLevelList();

	backgroundSprite.setPosition(0,0);
	backgroundSprite.setTexture(* game->getTexture("terminal_bg"));

	float xPosition = 32.0f;

	for (auto &level : levelData["levels"])
	{
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

		auto button = std::make_shared<Button>(
			game->getTexture("lvl_normal"),
			game->getTexture("lvl_hover"),
			game->getTexture("lvl_click"),
			sf::Vector2f(xPosition, 32),
			game,
			[levelName, game]()
			{
				auto newGame = game->getGame();
				auto combat = std::make_shared<Combat>(newGame, levelName);
				newGame->pushState(combat, true);
				combat->initComponents();
			}
		);

		auto text = sf::Text(levelName, * game->getFont("font_small"), 8);
		text.setPosition(xPosition + 3, 31);
		text.setFillColor(sf::Color(0xdd, 0xdd, 0xdd));

		levelList.push_back(std::make_pair(text, button));

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
	for (auto pair : levelList)
	{
		pair.second->handleEvent(event);
	}

	backButton.handleEvent(event);
	homeButton.handleEvent(event);
}

void Terminal::update()
{
	for (auto pair : levelList)
	{
		pair.second->update();
	}
	backButton.update();
	homeButton.update();
}

void Terminal::render(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);

	for (auto pair : levelList)
	{
		pair.second->render(window);
		window.draw(pair.first);
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

void Terminal::playMusic()
{
    if(game->bgMusic) game->bgMusic->stop();
    game->bgMusic = game->getMusic("main_bg_music");
    game->bgMusic->setLoop(true);
    game->bgMusic->play();
    std::clog << "Playing main menu music" << std::endl;
}
