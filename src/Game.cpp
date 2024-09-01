#include "Game.h"
#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"

Game::Game()
{
	window.create(sf::VideoMode(800, 600), "Pixnights");
	window.setFramerateLimit(60);
}

Game::~Game()
{
	while (!uiStack.empty())
	{
		uiStack.pop();
	}
}

void Game::pushState(std::unique_ptr<UserInterface> ui)
{
	uiStack.push(std::move(ui));
}

void Game::popState()
{
	uiStack.pop();
}

void Game::run()
{
	while (window.isOpen())
	{
		handleInput();
		if (!uiStack.empty())
		{
			uiStack.top()->update();
			uiStack.top()->render(window);
		}
		else
		{
			window.close();
		}
	}
}

void Game::handleEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (!uiStack.empty())
		{
			uiStack.top()->handleEvent(event);
		}
	}
}

void Game::loadAssets()
{
	auto load = [&](AssetType type, std::string name, std::string filename)
	{
		loadSingleAsset(type, name, ASSET_PREFIX + filename);
	};
	// load global assets here, TODO
}

void Game::loadSingleAsset(const AssetType assetType, const std::string &name, const std::string &filename)
{
	switch (assetType)
	{
	case TEXTURE:
		assetManager.loadTexture(name, filename);
		break;

	case MUSIC:
		assetManager.loadMusic(name, filename);
		break;

	case FONT:
		assetManager.loadFont(name, filename);

	default:
		break;
	}
}

void Game::init()
{
	auto load = [&](AssetType type, std::string name, std::string filename)
	{
		loadSingleAsset(type, name, ASSET_PREFIX + filename);
	};

	load(TEXTURE, "splash_bg_img", "image/splash/bg.png");
	load(MUSIC, "splash_bg_music", "audio/m_sys_title_combine.mp3");

	load(TEXTURE, "start_normal", "image/splash/start_normal.png");
	load(TEXTURE, "start_hover", "image/splash/start_hover.png");
	load(TEXTURE, "start_click", "image/splash/start_click.png");

	pushState(std::make_unique<SplashScreen>(
		assetManager.getTexture("splash_bg_img"),
		assetManager.getMusic("splash_bg_music"),
		assetManager.getTexture("start_normal"),
		assetManager.getTexture("start_hover"),
		assetManager.getTexture("start_click"),
		shared_from_this()));

	loadAssets();
}