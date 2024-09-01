#include "Game.h"
#include "UserInterface.h"
#include "SplashScreen.h"
#include "MainMenu.h"

#include <iostream>

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), "Pixnights");
	window.setFramerateLimit(60);

	view.setSize(192, 108);
	view.setCenter(192 / 2, 108 / 2);
}

Game::~Game()
{
	while (!uiStack.empty())
	{
		uiStack.pop();
	}
}

void Game::updateView()
{
    sf::Vector2f windowSize(window.getSize());
    sf::Vector2f targetSize(192, 108);

    // 计算窗口和目标的宽高比
    float windowRatio = windowSize.x / windowSize.y;
    float targetRatio = targetSize.x / targetSize.y;
    sf::FloatRect viewport;

    if (windowRatio > targetRatio)
    {
        // 窗口宽于目标宽高比
        float scale = windowSize.y / targetSize.y;
        float width = targetSize.x * scale;
        float left = (windowSize.x - width) / 2.0f / windowSize.x;
        viewport = sf::FloatRect(left, 0.0f, width / windowSize.x, 1.0f);
    }
    else
    {
        // 窗口高于目标宽高比
        float scale = windowSize.x / targetSize.x;
        float height = targetSize.y * scale;
        float top = (windowSize.y - height) / 2.0f / windowSize.y;
        viewport = sf::FloatRect(0.0f, top, 1.0f, height / windowSize.y);
    }

    view.setSize(targetSize);
    view.setCenter(targetSize.x / 2, targetSize.y / 2);
    view.setViewport(viewport);

    window.setView(view);
}


sf::Vector2f Game::getMousePosition()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	return window.mapPixelToCoords(mousePosition);
}

void Game::pushState(std::unique_ptr<UserInterface> ui)
{
	uiStack.push(std::move(ui));
}

void Game::popState()
{
	uiStack.pop();
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

void Game::run()
{
	while (window.isOpen())
	{
		handleEvent();
		window.clear();
		if (!uiStack.empty())
		{
			window.setView(view);
			uiStack.top()->update();
			uiStack.top()->render(window);
		}
		else
		{
			window.close();
		}
		window.display();
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
		else if (event.type == sf::Event::Resized)
		{
			updateView();
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