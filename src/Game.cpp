#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(800, 600), "Pixnights");
	window.setFramerateLimit(60);
}

Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{
		handleInput();
		update();
		render();
	}
}

void Game::handleEvent(const sf::Event &event)
{
	sf::Event e = event;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		handleInput();
	}
}

void Game::update()
{
}

void Game::render() // prototype, DON'T USE
{}


void Game::handleInput()
{
}

void Game::loadAssets()
{
	auto load = [&](AssetType type, std::string name, std::string filename)
	{
		loadSingleAsset(type, name, ASSET_PREFIX + filename);
	};

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
	stateStack.push(SPLASH_SCREEN);
	currState = SPLASH_SCREEN;

	auto load = [&](AssetType type, std::string name, std::string filename)
	{
		loadSingleAsset(type, name, ASSET_PREFIX + filename);
	};

	load(TEXTURE, "splash_bg_img", "image/splash/bg.png");
	load(MUSIC, "splash_bg_music", "audio/m_sys_title_combine.mp3");

	load(TEXTURE, "start_normal", "image/splash/start_normal.png");
	load(TEXTURE, "start_hover", "image/splash/start_hover.png");
	load(TEXTURE, "start_click", "image/splash/start_click.png");

	splashScreen = std::make_unique<SplashScreen>(
		assetManager.getTexture("splash_bg_img"),
		assetManager.getMusic("splash_bg_music"),
		assetManager.getTexture("start_normal"),
		assetManager.getTexture("start_hover"),
		assetManager.getTexture("start_click"),
		currState);

	loadAssets();
}